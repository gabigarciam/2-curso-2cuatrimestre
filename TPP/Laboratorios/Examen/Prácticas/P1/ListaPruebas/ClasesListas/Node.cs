using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClasesListas
{
    internal class Node
    {
        private int value;
        private Node next;

        public Node(int value, Node next)
        {
            this.value = value;
            this.next = next;
        }

        public Node(int value)
        {
            this.value = value;
            this.next = null;
        }

        public Node GetNext
        {
            get { return next; }
            set { this.next = value; }
        }

        public int GetValue
        {
            get { return value; }
            set { this.value = value; }
        }
    }
}
