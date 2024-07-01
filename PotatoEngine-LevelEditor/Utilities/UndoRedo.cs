using System.Collections.ObjectModel;
using System.Diagnostics;

namespace PotatoEngine_LevelEditor.Utilities
{
    public interface IUndoRedo
    {
        string Name { get; }

        void Undo()
        {

        }

        void Redo()
        {

        }
    }

    public class UndoRedoAction : IUndoRedo
    {
        private Action _undoAction;
        private Action _redoAction;

        public string Name { get; }

        public void Redo() => _redoAction();

        public void Undo() => _undoAction();

        public UndoRedoAction(string name)
        {
            Name = name;
        }

        public UndoRedoAction(Action undo, Action redo, string name)
            : this(name)
        {
            Debug.Assert(undo != null && redo != null);
            _undoAction = undo;
            _redoAction = redo;
        }
    }

    public class UndoRedo
    {
        private readonly ObservableCollection<IUndoRedo> _rendoList = new ObservableCollection<IUndoRedo>();
        private readonly ObservableCollection<IUndoRedo> _undoList = new ObservableCollection<IUndoRedo>();
        public ReadOnlyObservableCollection<IUndoRedo> RedoList { get; }
        public ReadOnlyObservableCollection<IUndoRedo> UndoList { get; }

        public void Reset()
        {
            _rendoList.Clear();
            _undoList.Clear();
        }

        public void Add(IUndoRedo cmd)
        {
            _undoList.Add(cmd);
            _rendoList.Clear();
        }

        public void Undo()
        {
            if(_undoList.Any())
            {
                var cmd = _undoList.Last();
                _undoList.RemoveAt(_undoList.Count - 1);
                cmd.Undo();
                _rendoList.Insert(0, cmd);
            }    
        }

        public void Redo()
        {
            if (_rendoList.Any())
            {
                var cmd = _rendoList.First();
                _rendoList.RemoveAt(0);
                cmd.Redo();
                _undoList.Add(cmd);
            }
        }

        public UndoRedo()
        {
            RedoList = new ReadOnlyObservableCollection<IUndoRedo>(_rendoList);
            UndoList = new ReadOnlyObservableCollection<IUndoRedo>(_undoList);
        }
    }
}
