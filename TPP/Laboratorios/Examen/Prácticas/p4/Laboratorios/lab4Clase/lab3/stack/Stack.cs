using System;
using System.Text;
using System.Diagnostics;
using TPPCollections;

namespace TPP.Laboratory.ObjectOrientation.Lab03 {

    public class Stack {

        private uint _maxNumberOfElements;
        private TPPList<int> list;

        public Stack(uint maxNumberOfElements)
        {
            _maxNumberOfElements = maxNumberOfElements;
            list = new TPPList<int>();
        }

        public bool IsEmpty
        {
            get { return list.IsEmpty(); }
        }

        public bool IsFull
        {
            get { return list.GetNumberOfElements == _maxNumberOfElements; }
        }

        public int GetNumberOfElements
        {
            get { return list.GetNumberOfElements; }
        }

        public bool Push(int element)
        {
            if (list.GetNumberOfElements < _maxNumberOfElements) {
                list.Add(element);
                return true;
            } else
            {
                return false;
            }
        } 

        public int Pop()
        {
            int element = list.GetElement(GetNumberOfElements);
            list.Remove(element);
            return element;
        }
    }

}