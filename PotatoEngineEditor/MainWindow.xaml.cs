using PotatoEngineEditor.GameProject;
using System.ComponentModel;
using System.IO;
using System.Windows;

namespace PotatoEngineEditor
{
    public partial class MainWindow : Window
    {
        public static string PotatoPath { get; private set; }

        public MainWindow()
        {
            InitializeComponent();
            Loaded += OnMainWindowLoaded;
            Closing += OnMainWindowClosing;
        }

        private void OnMainWindowLoaded(object sender, RoutedEventArgs e)
        {
            Loaded -= OnMainWindowLoaded;
            GetEnginePath();
            OpenProjectBrowserDialog();
        }

        private void GetEnginePath()
        {
            var potatoPath = Environment.GetEnvironmentVariable("POTATO_ENGINE", EnvironmentVariableTarget.User);
            if (potatoPath == null || !Directory.Exists(Path.Combine(potatoPath, @"PotatoEngine\EngineAPI")))
            {
                var dlg = new EnginePathDialog();
                if (dlg.ShowDialog() == true)
                {
                    PotatoPath = dlg.PotatoPath;
                    Environment.SetEnvironmentVariable("POTATO_ENGINE", PotatoPath.ToUpper(), EnvironmentVariableTarget.User);
                }
                else
                {
                    Application.Current.Shutdown();
                }
            }
            else
            {
                PotatoPath = potatoPath;
            }
        }

		private void OnMainWindowClosing(object sender, CancelEventArgs e)
		{
			Closing -= OnMainWindowClosing;
			Project.Current?.Unload();
		}

        private void OpenProjectBrowserDialog()
        {
            var projectBrowser = new ProjectBrowserDialog();
            if (projectBrowser.ShowDialog() == false || projectBrowser.DataContext == null)
            {
                Application.Current.Shutdown();
            }
            else
            {
                Project.Current?.Unload();
                DataContext = projectBrowser.DataContext;
            }
        }
    }
}