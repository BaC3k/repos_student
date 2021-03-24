using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _5Laba
{
    public partial class Form1 : Form
    {
        MiniList<CheckBox> v;
        IEnumerator<CheckBox> ven;
        IEnumerator<CheckBox> vn;
        public Form1()
        {
            InitializeComponent();
        }

        private void создатьСписокToolStripMenuItem_Click(object sender, EventArgs e)
        {
            v = new MiniList<CheckBox>();
            toolStripStatusLabel1.Text = "Список создан.";
        }

        private void добавитьЭлементToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (v != null)
            {
                CheckBox vcb = new CheckBox();
                vcb.Appearance = Appearance.Button;
                vcb.FlatStyle = FlatStyle.Standard;
                vcb.Top = 50;
                vcb.Width = 30;
                vcb.Left = 7 + 33 * v.Append(vcb);
                vcb.Text = Convert.ToString(vcb.Left);
                panel1.Controls.Add(vcb);
                toolStripStatusLabel1.Text = "";
            }
            else toolStripStatusLabel1.Text = "Список не создан.";
        }

        private void создатьЭнумераторToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (v != null)
            {
                ven = v.GetEnumerator();
                toolStripStatusLabel1.Text = "Энумератор создан.";
            }
            else toolStripStatusLabel1.Text = "Список не создан!";
        }

        private void moveNextToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                if (ven != null)
                    if (ven.MoveNext())
                    {
                        ven.Current.CheckState = CheckState.Checked;
                        toolStripStatusLabel1.Text = "O.K.";
                    }
                    else toolStripStatusLabel1.Text = "Конец списка!";
                else toolStripStatusLabel1.Text = "Энумератор не создан!";
            }
            catch (ListIsEmpty) { toolStripStatusLabel1.Text = "Список пуст!"; }
        }

        private void currentToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                if (ven != null)
                    if (ven.Current.CheckState == CheckState.Checked)
                        ven.Current.CheckState = CheckState.Unchecked;
                    else ven.Current.CheckState = CheckState.Checked;
                else toolStripStatusLabel1.Text = "Энумератор не создан!";
            }
            catch (InvalidOperationException) { toolStripStatusLabel1.Text = "Перебор не начат!"; }
        }

        private void resetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "";
            if (ven != null) { ven.Reset(); toolStripStatusLabel1.Text = "Энумератор обновлён!"; }
            else toolStripStatusLabel1.Text = "Энумератор не создан!";
        }

        private void создатьЭнумераторToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (v != null)
            {
                vn = v.GetEnumerator();
                toolStripStatusLabel1.Text = "Энумератор создан.";
            }
            else toolStripStatusLabel1.Text = "Список не создан!";
        }

        private void moveNextToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            try
            {
                if (vn != null)
                    if (vn.MoveNext())
                    {
                        (vn.Current as CheckBox).CheckState = CheckState.Checked;
                        toolStripStatusLabel1.Text = "O.K.";
                    }
                    else toolStripStatusLabel1.Text = "Конец списка!";
                else toolStripStatusLabel1.Text = "Энумератор объектов не создан!";
            }
            catch (ListIsEmpty) { toolStripStatusLabel1.Text = "Список пуст!"; }
        }

        private void currentToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            try
            {
                if (vn != null)
                    if ((vn.Current as CheckBox).Checked)
                        (vn.Current as CheckBox).CheckState = CheckState.Unchecked;
                    else (vn.Current as CheckBox).CheckState = CheckState.Checked;
                else toolStripStatusLabel1.Text = "Энумератор объектов не создан!";
            }
            catch (InvalidOperationException) { toolStripStatusLabel1.Text = "Перебор не начат!"; }
        }

        private void resetToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "";
            if (vn != null) { vn.Reset(); toolStripStatusLabel1.Text = "Энумератор объектов обновлён!"; }
            else toolStripStatusLabel1.Text = "Энумератор объектов не создан!";
        }


        class MiniList<T> : IEnumerable<T>
        {
            public Node Top;
            static int num;
            public class Node
            {
                public T content;
                public Node Next = null;
            }

            public int GetNum() { return num; }

            public int Append(T s)
            {
                Node p = new Node();
                p.content = s;
                if (Top != null) p.Next = Top;
                Top = p;
                return num++;
            }
            public IEnumerator<T> GetEnumerator()
            {
                return new Numerator(this);
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return new Numerator(this);
            }

            public class Numerator : IEnumerator<T>
            {
                bool active = false;
                MiniList<T> lst;
                Node current = null;
                public Numerator(MiniList<T> vl)
                {
                    lst = vl;
                }
                T IEnumerator<T>.Current
                {
                    get
                    {
                        if (current == null || !active) throw new InvalidOperationException();
                        else return current.content;
                    }
                }
                object IEnumerator.Current
                {
                    get
                    {
                        if (current == null || !active) throw new InvalidOperationException();
                        else return current.content;
                    }
                }
                public bool MoveNext()
                {
                    if (active)
                        if (current.Next == null) return false;
                        else current = current.Next;
                    else if (lst.Top != null)
                    {
                        active = true;
                        current = lst.Top;
                    }
                    else throw new ListIsEmpty();
                    return true;
                }
                public void Reset()
                {
                    active = false;
                    current = lst.Top;
                }
                public void Dispose() { current = null; }
            }
        }

        class ListIsEmpty : InvalidOperationException { }

        private void среднееГеометрическоеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            double sum = 1, n = 0;
            if (v != null)
            {
                ven = v.GetEnumerator();
                if (ven != null)
                {
                    ven.MoveNext();
                    sum *= ven.Current.Left;
                    n++;
                    while (ven.MoveNext())
                    {
                        sum *= ven.Current.Left;
                        n++;
                    }
                    toolStripStatusLabel1.Text = (Math.Pow(sum, 1 / n)).ToString();
                }
                else toolStripStatusLabel1.Text = "Энумератор не создан!";
            }
            else toolStripStatusLabel1.Text = "Список не создан!";
        }

        private void среднееАрифметическоеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            double sum = 0, n = 0;
            if (v != null)
            {
                ven = v.GetEnumerator();
                if (ven != null)
                {
                    ven.MoveNext();
                    sum += ven.Current.Left;
                    n++;
                    while (ven.MoveNext())
                    {
                        sum += ven.Current.Left;
                        n++;
                    }
                    toolStripStatusLabel1.Text = (sum / n).ToString();
                }
                else toolStripStatusLabel1.Text = "Энумератор не создан!";
            }
            else toolStripStatusLabel1.Text = "Список не создан!";
        }
    }
}
