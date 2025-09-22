using System.Windows;
using System.Windows.Threading;
using Wpf.Ui.Appearance;

namespace DataUI.UI.ViewModels
{
    public interface IMessageHost
    {
        Task ShowMessageBoxAsync(string title, string content);
    }

    public interface IWindowViewModelHost : IMessageHost
    {
        event RoutedEventHandler? Loaded;
        event ThemeChangedEvent? ThemeChanged;

        ResourceDictionary ApplicationResources { get; }

        ResourceDictionary WindowResources { get; }

        Dispatcher Dispatcher { get; }
    }
}
