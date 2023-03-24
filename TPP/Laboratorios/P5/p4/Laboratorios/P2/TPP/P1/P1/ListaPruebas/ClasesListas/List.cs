using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClasesListas
{
    public class List
    {
        private Node head;
        private int numberOfElements;

        public List()
        {
            head = null;
        }

        public void Add(int value)
        {
            Node nodo = new Node(value);
            Node nodoActual = head;

            if (head == null)
            {
                head = nodo;
                numberOfElements++;
            }
            else
            {
                while (nodoActual.GetNext != null)
                {
                    nodoActual = nodoActual.GetNext;
                }
                nodoActual.GetNext = new Node(value);
                numberOfElements++;
            }
        }

        public void Remove(int value)
        {
            Node nodoActual = head;
            if (nodoActual.GetValue == value)
            {
                head = nodoActual.GetNext;
                numberOfElements--;
            }
            else if (nodoActual.GetNext.GetValue == value)
            {
                nodoActual.GetNext = nodoActual.GetNext.GetNext;
                numberOfElements--;
            }
            else
            {
                while (nodoActual.GetNext.GetValue != value)
                {
                    nodoActual = nodoActual.GetNext;
                }
                nodoActual.GetNext = nodoActual.GetNext.GetNext;
                numberOfElements--;
            }
        }

        public int GetElement(int pos)
        {
            Node nodoActual = head;
            for (int i = 0; i < pos; i++)
            {
                if(nodoActual.GetNext== null)
                {
                    return -1;
                }
                else
                {
                    nodoActual= nodoActual.GetNext;
                }
            } 
            return nodoActual.GetValue;
        }

        public int GetNumberOfElements
        {
            get { return numberOfElements; }
        }
    }
}
