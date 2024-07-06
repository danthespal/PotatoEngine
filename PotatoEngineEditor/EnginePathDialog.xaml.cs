using System.IO;
using System.Windows;

namespace PotatoEngineEditor
{
    public partial class EnginePathDialog : Window
    {
        public string PotatoPath { get; private set; }

        public EnginePathDialog()
        {
            InitializeComponent();
            Owner = Application.Current.MainWindow;
        }

        private void OnOk_Button_Click(object sender, RoutedEventArgs e)
        {
            var path = pathTextBox.Text.Trim();
            messageTextBlock.Text = string.Empty;
            if (string.IsNullOrEmpty(path))
            {
                messageTextBlock.Text = "Invalid path.";
            }
            else if (path.IndexOfAny(Path.GetInvalidPathChars()) != -1)
            {
                messageTextBlock.Text = "Invalid character(s) used in path.";
            }
            else if (!Directory.Exists(Path.Combine(path, @"PotatoEngine\EngineAPI")))
            {
                messageTextBlock.Text = "Unable to find the engine at the specified location.";
            }
            if (string.IsNullOrEmpty(messageTextBlock.Text))
            {
                if (!Path.EndsInDirectorySeparator(path)) path += @"\";
                PotatoPath = path;
                DialogResult = true;
                Close();
            }
        }
    }
}
