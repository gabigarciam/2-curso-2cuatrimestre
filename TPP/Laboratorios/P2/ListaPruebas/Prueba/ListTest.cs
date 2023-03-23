using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using ClasesListas;
using System.Numerics;

namespace Prueba
{
    [TestClass]
    public class ListTest
    {

        private List<int> listaInt;
        private List<String> listaString;
        private List<double> listaDouble;

        /// <summary>
        /// This class (static) method is run only once, before running any test.
        /// Used for initialization purposes to assign the resoures used by all the tests in this class.
        /// The attribute (annotation) between [] allows using any static method with any name.
        /// It is not necessary to be written if it is not used.
        /// </summary>
        [ClassInitialize]
        public static void InitializeAllTheTests(TestContext testContext)
        {
        }

        /// <summary>
        /// Method that executed before each single test in this class.
        /// Used to initialize all the tests in the class.
        /// The attribute (annotation) between [] allows using any static method with any name.
        /// It is not necessary to be written if it is not used.
        /// </summary>
        [TestInitialize]
        public void InitializeTests()
        {
            this.listaInt= new List<int>();
            this.listaString= new List<string>();
            this.listaDouble = new List<double>();
        }
        /// <summary>
        /// Method that executed after each single test in this class.
        /// Used to clean up all the tests in the class.
        /// The attribute (annotation) between [] allows using any static method with any name.
        /// It is not necessary to be written if it is not used.
        /// </summary>
        [TestCleanup]
        public void CleanUpTests()
        {
        }

        /// <summary>
        /// This class (static) method is run only once, after running all the tests.
        /// Used for cleaning up purposes, to release the resources used by all the tests in this class.
        /// The attribute (annotation) between [] allows using any static method with any name.
        /// It is not necessary to be written if it is not used.
        /// </summary>
        [ClassCleanup]
        public static void CleanUpAllTheTests()
        {
        }

        /********************** Tesing methods *********************************/

        [TestMethod]
        public void TestListInt()
        {
            listaInt.Add(1);
            listaInt.Add(2);
            listaInt.Add(3);
            Assert.IsTrue(listaInt.contains(1));
            Assert.IsTrue(listaInt.contains(2));
            Assert.IsTrue(listaInt.contains(3));
            Assert.AreEqual(1, listaInt.GetElement(0));
            Assert.AreEqual(2, listaInt.GetElement(1));
            Assert.AreEqual(3, listaInt.GetElement(2));
            Assert.AreEqual(3, listaInt.GetNumberOfElements);

            Assert.IsTrue(listaInt.Remove(1));
            Assert.IsFalse(listaInt.contains(1));
            Assert.AreEqual(0, listaInt.GetElement(3));
            Assert.AreEqual(2, listaInt.GetElement(0));
            Assert.AreEqual(3, listaInt.GetElement(1));
            Assert.AreEqual(2, listaInt.GetNumberOfElements);
        }

        [TestMethod]
        public void TestListString()
        {
            listaString.Add("A");
            listaString.Add("B");
            listaString.Add("C");
            Assert.IsTrue(listaString.contains("A"));
            Assert.IsTrue(listaString.contains("B"));
            Assert.IsTrue(listaString.contains("C"));
            Assert.AreEqual("A", listaString.GetElement(0));
            Assert.AreEqual("B", listaString.GetElement(1));
            Assert.AreEqual("C", listaString.GetElement(2));
            Assert.AreEqual(3, listaString.GetNumberOfElements);

            Assert.IsTrue(listaString.Remove("A"));
            Assert.IsFalse(listaString.contains("A"));
            Assert.AreEqual("B", listaString.GetElement(0));
            Assert.AreEqual("C", listaString.GetElement(1));
            Assert.AreEqual(null, listaString.GetElement(2));
            Assert.AreEqual(2, listaString.GetNumberOfElements);
        }

        [TestMethod]
        public void TestListDouble()
        {
            listaDouble.Add(1.4);
            listaDouble.Add(9.9);
            listaDouble.Add(3.3);
            Assert.IsTrue(listaDouble.contains(1.4));
            Assert.IsTrue(listaDouble.contains(9.9));
            Assert.IsTrue(listaDouble.contains(3.3));
            Assert.AreEqual(1.4, listaDouble.GetElement(0));
            Assert.AreEqual(9.9, listaDouble.GetElement(1));
            Assert.AreEqual(3.3, listaDouble.GetElement(2));
            Assert.AreEqual(3, listaDouble.GetNumberOfElements);

            Assert.IsTrue(listaDouble.Remove(9.9));
            Assert.IsFalse(listaDouble.contains(9.9));
            Assert.AreEqual(1.4, listaDouble.GetElement(0));
            Assert.AreEqual(3.3, listaDouble.GetElement(1));
            Assert.AreEqual(2, listaDouble.GetNumberOfElements);
            
            Assert.IsTrue(listaDouble.contains(3.3));
        }
    }
}
