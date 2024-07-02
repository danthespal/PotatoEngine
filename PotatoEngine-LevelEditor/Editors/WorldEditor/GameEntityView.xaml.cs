using System.Windows.Controls;

namespace PotatoEngine_LevelEditor.Editors
{
    /// <summary>
    /// Interaction logic for GameEntityView.xaml
    /// </summary>
    public partial class GameEntityView : UserControl
    {
        public static GameEntityView Instance { get; private set; }
        public GameEntityView()
        {
            InitializeComponent();
            DataContext = null;
            Instance = this;
        }
    }
}
