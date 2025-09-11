using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.CompilerServices;

namespace DataUI.UI.ViewModels
{
    public class ObservableModel : INotifyPropertyChanged
    {
        #region INotifyPropertyChanged Implementation

        public event PropertyChangedEventHandler? PropertyChanged;

        #endregion

        #region Methods

        public virtual void NotifyPropertyChanged([CallerMemberName] string? propertyName = default)
        {
            Debug.Assert(!string.IsNullOrEmpty(propertyName));

            FirePropertyChangedEvent(this, new PropertyChangedEventArgs(propertyName));
        }

        public virtual void NotifyPropertyChanged(params string[] propertyNames)
        {
            Debug.Assert(propertyNames != default &&
                         propertyNames.Length > 0);

            foreach (var propertyName in propertyNames)
            {
                NotifyPropertyChanged(propertyName);
            }
        }

        #endregion

        #region Protected Methods

        protected virtual void FirePropertyChangedEvent(object sender, PropertyChangedEventArgs e)
        {
            PropertyChanged?.Invoke(sender, e);
        }

        #endregion
    }
}
