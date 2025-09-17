using DataSrvLib;
using DataUI.UI.Converters;
using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;
using System.Diagnostics;
using System.Windows;
using System.Windows.Media;
using System.Windows.Threading;
using Wpf.Ui.Markup;

namespace DataUI.UI.ViewModels
{
    public class MainWindowViewModel : ObservableModel
    {
        #region Properties

        public PlotModel PlotModel {  get; init; } = new PlotModel();

        ResourceDictionary? Resources { get; set; } = default;

        Dispatcher? Dispatcher { get; set; } = default;

        CPUTempData? CPUProvider { get; set; } = default;

        IList<float> Values { get; set; } = new List<float>();

        #endregion

        #region Construction

        public void Initialize(ResourceDictionary resources, Dispatcher dispatcher)
        {
            Debug.Assert(resources != default);
            Debug.Assert(dispatcher != default);

            Resources = resources;
            Dispatcher = dispatcher;

            Values = Enumerable.Repeat(0.0f, 100).ToList();
            BuildPlotModel();

            var obj = new DataProvider();

            CPUProvider = obj.CpuTemp;
            CPUProvider.OnNextSample += OnNextSample;
        }

        public void Dispose()
        {
            if (CPUProvider != null)
            {
                CPUProvider.OnNextSample -= OnNextSample;
                CPUProvider = null;
            }
        }

        #endregion

        #region Event Handlers

        void OnNextSample(float value)
        {
            Dispatcher?.Invoke(() => AddSample(value));
        }

        #endregion

        #region Helper Methods

        void BuildPlotModel()
        {
            var series = new AreaSeries();
            series.StrokeThickness = 1;
            series.Points.AddRange(Values.Select((v, i) => new DataPoint(i, v)));

            var axisTemp = new LinearAxis();
            axisTemp.Position = AxisPosition.Left;
            axisTemp.Minimum = 0;
            axisTemp.Maximum = 100;
            axisTemp.MajorGridlineStyle = LineStyle.Solid;
            axisTemp.MinorGridlineStyle = LineStyle.Solid;
            axisTemp.IsPanEnabled = false;
            axisTemp.IsZoomEnabled = false;

            var axisSample = new LinearAxis();
            axisSample.Position = AxisPosition.Bottom;
            axisSample.TickStyle = TickStyle.None;
            axisSample.IsPanEnabled = false;
            axisSample.IsZoomEnabled = false;
            axisSample.IsAxisVisible = false;

            PlotModel.Axes.Add(axisTemp);
            PlotModel.Axes.Add(axisSample);
            PlotModel.Series.Add(series);

            BindPlotColors();
            BindTextTitels();

            PlotModel.InvalidatePlot(true);
        }

        void BindPlotColors()
        {
            if (Resources == default)
            {
                return;
            }

            var converter = new ColorToOxyPlotColorConverter();
            var background = converter.Convert((Color)Resources[ThemeResource.ApplicationBackgroundColor.ToString()]);
            var border = converter.Convert((Color)Resources[ThemeResource.ControlStrokeColorDefault.ToString()]);
            var text = converter.Convert((Color)Resources[ThemeResource.TextFillColorPrimary.ToString()]);
            var title = converter.Convert((Color)Resources[ThemeResource.TextFillColorSecondary.ToString()]);
            var subTitle = converter.Convert((Color)Resources[ThemeResource.TextFillColorTertiary.ToString()]);
            var majorGrid = converter.Convert((Color)Resources[ThemeResource.TextFillColorTertiary.ToString()]);
            var minorGrid = OxyColor.FromAColor(0x30, majorGrid);
            var seriesStroke = converter.Convert((Color)Resources[ThemeResource.SystemAccentColorPrimary.ToString()]);
            var seriesFill = OxyColor.FromAColor(0x30, seriesStroke);

            PlotModel.Background = background;
            PlotModel.PlotAreaBackground = background;
            PlotModel.PlotAreaBorderColor = border;
            PlotModel.TextColor = text;
            PlotModel.TitleColor = title;
            PlotModel.SubtitleColor = subTitle;

            var axisTemp = PlotModel.Axes.Cast<LinearAxis>()
                                         .FirstOrDefault(a => a.Position == AxisPosition.Left);
            if (axisTemp != default)
            {
                axisTemp.TitleColor = title;
                axisTemp.MajorGridlineColor = majorGrid;
                axisTemp.MinorGridlineColor = minorGrid;
            }

            var series = PlotModel.Series.ElementAtOrDefault(0) as AreaSeries;
            if (series != default)
            {
                series.Color = seriesStroke;
                series.Fill = seriesFill;
            }
        }

        void BindTextTitels()
        {
            if (Resources == default)
            {
                return;
            }

            var axisTemp = PlotModel.Axes.Cast<LinearAxis>()
                                         .FirstOrDefault(a => a.Position == AxisPosition.Left);
            if (axisTemp != default)
            {
                axisTemp.Title = (string)Resources["TemperatureLabel"];
                axisTemp.Unit = (string)Resources["CelsiusUnitLabel"];
            }
        }

        void AddSample(float value)
        {
            Values.RemoveAt(0);
            Values.Add(value);

            var series = PlotModel.Series.FirstOrDefault() as AreaSeries;
            if (series != default)
            {
                series.Points.Clear();
                series.Points.AddRange(Values.Select((v, i) => new DataPoint(i, v)));
            }

            var axisTemp = PlotModel.Axes.Cast<LinearAxis>()
                                         .FirstOrDefault(a => a.Position == AxisPosition.Left);
            if (axisTemp != default)
            {
                axisTemp.Minimum = Math.Max(Values.Min() - 30, 0);
            }

            PlotModel.InvalidatePlot(true);
        }

        #endregion
    }
}
