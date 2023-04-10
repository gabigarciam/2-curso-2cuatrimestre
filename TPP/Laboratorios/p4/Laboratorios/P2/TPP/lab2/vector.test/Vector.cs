using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vector.test
{
    internal class Vector
    {
        private int[] vector;
        private int size;
        public Vector()
        {
            vector = new int[1];
            size = 0;
        }

        public void Add(int element)
        {
            Array.Resize(ref vector, size + 1);
            vector[size] = element;
            size++;
        }

        public int Size { get; }

        public void SetElement(int element, int pos)
        {
            if(pos < size)
            {
                if(vector[pos] != null)
                {
                    vector[pos] = element;
                    size++;
                }
                else
                {
                    throw new System.ArgumentException();
                }
                
            } else
            {
               
            }
        }

        public int GetElement(int pos)
        {
            if (pos < size)
            {
                return vector[pos];
            } else
            {
                throw new System.ArgumentException();
            }
        }
    }
}
