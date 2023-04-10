using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tpplist
{
    internal class ListEnumerator<T> : IEnumerator<T>
    {
        int index;
        int maxNumberOfElements;
        Node<T> current;
        Node<T> nextNode;
        Node<T> _head;

        public ListEnumerator(Node<T> head, int maxNumberOfElements)
        {
            this._head = head;
            this.maxNumberOfElements = maxNumberOfElements;
            Reset();
        }

        T IEnumerator<T>.Current
        {
            get { return current.GetValue; }
        }

        object IEnumerator.Current
        {
            get { return current.GetValue; }
        }

        public bool MoveNext()
        {
            if (index >= maxNumberOfElements)
            {
                return false;
            }
            if (index == 0)
            {
                index++;
                return true;
            }
            if (nextNode.GetNext != null)
            {
                Node<T> aux = nextNode;
                nextNode = nextNode.GetNext;
                current = aux;
                index++;
                return true;
            }
            current = nextNode;
            nextNode = null;
            index++;
            return true;
        }

        public void Reset()
        {
            index = 0;
            current = _head;
            nextNode = _head.GetNext;
        }

        public void Dispose()
        {
        }
    }
}
