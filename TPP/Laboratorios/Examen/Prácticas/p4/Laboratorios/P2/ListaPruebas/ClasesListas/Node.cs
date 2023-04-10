using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TPPCollections
{
    public class Node<T>
    {
        private T _value;
        private Node<T> _next;

        public Node(T value, Node<T> next)
        {
            this._value = value;
            this._next = next;
        }

        public Node(T value)
        {
            this._value = value;
            this._next = null;
        }

        public Node<T> GetNext
        {
            get { return _next; }
            set { this._next = value; }
        }

        public T GetValue
        {
            get { return _value; }
            set { this._value = value; }
        }

        public override string ToString()
        {
            return _value.ToString();
        }
    }
}
