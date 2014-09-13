using System;
//using System.Collections;

namespace Learning
{
    internal struct StackEl
    {
        ValueType data;
        StackEl addr;
        StackEl(ValueType data, StackEl addr)
        {
            this.data = data;
            this.addr = addr;
        }
        public override string ToString()
        {
            return (String.Format("({0}, {1})", this.data, this.addr));
        }
    }

    public class Stack
    {
        private StackEl top;
        Stack()
        {
            this.top = null;
        }
        public void Push(ValueType data)
        {
            StackEl newEl = new StackEl(data, top);
            this.top = newEl;
        }

        public ValueType Pop()
        {
            ValueType result = this.top.data;
            this.top = this.top.addr;
            return result;
        }


    }

    class ArrayTools
    {
        public static void PrintVector(int[] v)
        {
            Console.WriteLine("Vector:");
            foreach (int i in v)
            {
                Console.WriteLine(i);
            }
        }

        public static void MergeSorted(int[] v, int iBegin, int iMiddle, int iEnd, params int[] idx)
        {
            int i1 = iBegin, i2 = iMiddle;
            int[] vr = new int[v.Length];
            int[] idxr = new int[idx.Length];
            bool calcIdx = (idx != null);
            for (int j = iBegin; j < iEnd; j++)
            {
                if ((i2 == iEnd) || ((v[i1] < v[i2]) && (i1 < iMiddle)))
                {
                    if (calcIdx)
                    {
                        idxr[j] = idx[i1];
                    }
                    vr[j] = v[i1++];
                }
                else
                {
                    if (calcIdx)
                    {
                        idxr[j] = idx[i2];
                    }
                    vr[j] = v[i2++];
                }
            }
            for (int j = iBegin; j < iEnd; j++)
            {
                if (calcIdx)
                {
                    idx[j] = idxr[j];
                }
                v[j] = vr[j];
            }
        }

        public static void Split(int[] v, int iBegin, int iEnd, params int[] idx)
        {
            if (iEnd - iBegin < 2) return;
            int iMiddle = (iBegin + iEnd) / 2;
            Split(v, iBegin, iMiddle, idx);
            Split(v, iMiddle, iEnd, idx);
            MergeSorted(v, iBegin, iMiddle, iEnd, idx);
        }

        public static void Sort(int[] v, params int[] idx)
        {
            if (idx != null)
            {
                for (int i = 0; i < idx.Length; i++)
                {
                    idx[i] = i;
                }
            }
            Split(v, 0, v.Length, idx);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            //const int n = 10;
            //const int minVal = 0;
            //const int maxVal = 100;
            //int[] v = new int[n];
            //Random randNum = new Random();
            //for (int i = 0; i < v.Length; i++)
            //{
            //    v[i] = randNum.Next(minVal, maxVal);
            //}

            //ArrayTools.PrintVector(v);
            //int[] idx = new int[v.Length];
            //int[] vCopy = new int[v.Length];
            //Array.Copy(v, vCopy, v.Length);
            //ArrayTools.Sort(v, idx);
            //ArrayTools.PrintVector(idx);
            //Console.WriteLine("Array:");
            //foreach (int i in idx)
            //{
            //    Console.WriteLine(vCopy[i]);
            //}

            Stack st = new Stack();
            st.Push("First");
            st.Push(2);
            st.Push(4.5);

            foreach (object v in st)
            {
                Console.WriteLine(v);
            }
        }
    }
}