using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClasesListas
{
    public class List<T>: IEnumerable<T>
    {
        private Node<T> _head;
        private int numberOfElements;

        public List()
        {
            _head = null;
        }

        public void Add(T value)
        {
            Node<T> nodo = new Node<T>(value);
            Node<T> nodoActual = _head;

            if (_head == null)
            {
                _head = nodo;
                numberOfElements++;
            }
            else
            {
                while (nodoActual.GetNext != null)
                {
                    nodoActual = nodoActual.GetNext;
                }
                nodoActual.GetNext = new Node<T>(value);
                numberOfElements++;
            }
        }

        public Boolean Remove(T value)
        {
            Node<T> nodoActual = _head;
            if (nodoActual.GetValue.Equals(value))
            {
                _head = nodoActual.GetNext;
                numberOfElements--;
                return true;
            }
            else if (nodoActual.GetNext.GetValue.Equals(value))
            {
                nodoActual.GetNext = nodoActual.GetNext.GetNext;
                numberOfElements--;
                return true;
            }
            else
            {
                while (!nodoActual.GetNext.GetValue.Equals(value))
                {
                    nodoActual = nodoActual.GetNext;
                }
                nodoActual.GetNext = nodoActual.GetNext.GetNext;               
            }
            return false;
        }

        public Boolean contains(T value)
        {
            Node<T> nodoActual = _head;
            while(nodoActual != null)
            {
                if (nodoActual.GetValue.Equals(value))
                {
                    return true;
                }
                else
                {
                    nodoActual = nodoActual.GetNext;
                }
            }
            return false;
        }

        public Boolean IsEmpty()
        {
            if (numberOfElements == 0) return true;
            else return false;
        }

        public int GetNumberOfElements
        {
            get { return numberOfElements; }
        }

    

        public T GetElement(int pos)
        {
            Node<T> nodoActual = _head;
            for (int i = 0; i < pos; i++)
            {
                if(nodoActual.GetNext== null)
                {
                    return default(T);
                }
                else
                {
                    nodoActual= nodoActual.GetNext;
                }
            } 
            return nodoActual.GetValue;
        }

        public override string ToString()
        {
            Node<T> nodoActual = _head;
            StringBuilder sb = new StringBuilder();
            while(nodoActual != null)
            {
                sb.Append(nodoActual.ToString());
            }
            return sb.ToString();
        }

        public IEnumerator<T> GetEnumerator()
        {
            return new ListEnumerator<T>(_head, numberOfElements);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return new ListEnumerator<T>(_head, numberOfElements);
        }
    }
}
