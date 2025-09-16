using DataSrvLib;
using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;
using System.Windows;

namespace DataUI.UI.ViewModels
{
    public class MainWindowViewModel : ObservableModel
    {
        #region Properties

        public PlotModel PlotModel {  get; init; } = new PlotModel();

        CPUTempData? CPUProvider { get; set; } = default;

        IList<float> Values { get; set; } = new List<float>();

        #endregion

        #region Construction

        public void Initialize()
        {
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
            Application.Current.Dispatcher.Invoke(() => AddSample(value));
        }

        #endregion

        #region Helper Methods

        void BuildPlotModel()
        {
            var series = new LinearBarSeries();
            series.FillColor = OxyColor.FromArgb(69, 76, 175, 80);
            series.StrokeColor = OxyColor.FromArgb(255, 76, 175, 80);
            series.StrokeThickness = 1;
            series.Points.AddRange(Values.Select((v, i)=> new DataPoint(i, v)));

            var axisTemp = new LinearAxis();
            axisTemp.Position = AxisPosition.Left;
            axisTemp.Minimum = 0;
            axisTemp.Maximum = 100;
            axisTemp.MajorGridlineStyle = LineStyle.Solid;
            axisTemp.MinorGridlineStyle = LineStyle.Dot;
            axisTemp.IsZoomEnabled = false;

            var axisSample = new LinearAxis();
            axisSample.Position = AxisPosition.Bottom;
            axisSample.TickStyle = TickStyle.None;
            axisSample.IsAxisVisible = false;

            PlotModel.Axes.Add(axisTemp);
            PlotModel.Axes.Add(axisSample);
            PlotModel.Series.Add(series);
        }

        void AddSample(float value)
        {
            Values.RemoveAt(0);
            Values.Add(value);

            var series = PlotModel.Series.Cast<LinearBarSeries>().First()!;
            series.Points.Clear();
            series.Points.AddRange(Values.Select((v, i) => new DataPoint(i, v)));

            PlotModel.InvalidatePlot(true);
        }

        #endregion
    }
}
