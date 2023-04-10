using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TPP.Laboratory.Functional.Lab08 {

    class Query {

        private Model model = new Model();

        private static void Show<T>(IEnumerable<T> collection) {
            foreach (var item in collection) {
                Console.WriteLine(item);
            }
            Console.WriteLine("Number of items in the collection: {0}.", collection.Count());
        }

        static void Main(string[] args) {
            Query query = new Query();
            //query.Query1();
            //query.Query2();
            //query.Query3();
            //query.Query4();
            //query.Query5();
            query.Query6();
        }

        private void Query1() {
            // Modify this query to show the names of the employees older than 50 years
            var employees = model.Employees.Where(a => a.Age > 50).Select(e => e.Name);
            Console.WriteLine("Employees:");
            Show(employees);
        }

        private void Query2() {
            // Show the name and email of the employees who work in Asturias
            var employees = model.Employees.Where(a => a.Province.ToLower().Equals("Asturias")).Select(e => (e.Name, e.Surname));
            Console.WriteLine("Employees:");
            Show(employees);
        }

        private void Query2v2()
        {
            // Show the name and email of the employees who work in Asturias
            var employees = model.Employees.Where(a => a.Province.ToLower().Equals("Asturias")).Select(e => new { e.Name, e.Surname });
            Console.WriteLine("Employees:");
            Show(employees);
        }

        // Notice: from now on, check out http://msdn.microsoft.com/en-us/library/9eekhta0.aspx

        private void Query3() {
            // Show the names of the departments with more than one employee 18 years old and beyond; 
            // the department should also have any office number starting with "2.1"
            var departments = model.Departments.Where(d => d.Employees.Count(a => a.Age >= 18) >= 1).
                Where(n => n.Employees.Any(r => r.Office.Number.StartsWith("2.1"))).Select(d => d.Name);
            Console.WriteLine("Departments:");
            Show(departments);
        }

        private void Query4() {
            // Show the phone calls of each employee. 
            // Each line should show the name of the employee and the phone call duration in seconds.
            //var calls = model.Employees.Select(e => model.PhoneCalls.Where(c => c.SourceNumber.Equals(e.TelephoneNumber)));
            var calls = model.Employees.Join(model.PhoneCalls, 
                n=> n.TelephoneNumber, sn => sn.SourceNumber,(n,sn) => new
                {
                    n.Name,
                    sn.Seconds,
                });
            Console.WriteLine("Calls:");
            Show(calls);
        }

        private void Query5() {
            // Show, grouped by each province, the name of the employees 
            // (both province and employees must be lexicographically ordered)
            var groupedBy = model.Employees.OrderBy(r => r.Name).OrderBy(r=> r.Province).GroupBy(p => p.Province);
            Console.WriteLine("GroupedBy");
            foreach (var group in groupedBy)
            {
                Console.WriteLine(group.Key);
                Show(group);
            }
        }

        private void Query6()
        {
            // Rank the calls by duration. Show rank position and duration
            var rank = model.PhoneCalls.OrderByDescending(r => r.Seconds).Select(s => s.Seconds).Zip(Enumerable.Range(1, model.PhoneCalls.Count));
            Show(rank);
        }


        /************ Homework **********************************/

        private void Homework1() {
            // Show, ordered by age, the names of the employees in the Computer Science department, 
            // who have an office in the Faculty of Science, 
            // and who have done phone calls longer than one minute
            var employees = model.Employees.OrderBy(e => e.Age)//ordenados por edad
                .Where(e => e.Department.Name.ToLower().Equals("computer science"))//empleados pertenecientes al departamento computer science
                .Where(e => e.Office.Building.ToLower().Equals("faculty of science"))//despacho en la facultad de ciencias
                .Where(e => model.PhoneCalls.Where(c => c.SourceNumber.Equals(e.TelephoneNumber))
                .Any(c => c.Seconds >= 60)).Select(e => e.Name);
            Console.WriteLine("Employees:");
            Show(employees);
        }

        private void Homework2() {
            // Show the summation, in seconds, of the phone calls done by the employees
            // of the Computer Science department
            var calls = model.PhoneCalls.Where(c => model.Employees
            .Where(e => e.Department.Name.ToLower().Equals("computer science"))
            .Any(e => e.TelephoneNumber.Equals(c.SourceNumber))).Aggregate(0, (a, b) => a + b.Seconds);
            Console.WriteLine("Suma Llamadas:");
            Console.WriteLine(calls);
        }

        private void Homework3() {
            // Show the phone calls done by each department, ordered by department names. 
            // Each line must show “Department = <Name>, Duration = <Seconds>”
            var calls = model.Departments
                .OrderBy(d => d.Name)
                .Select(d => $"Department={d.Name} -- Duration=" +
                d.Employees.SelectMany(e => model.PhoneCalls.Where(c => c.SourceNumber.Equals(e.TelephoneNumber)))
                .Aggregate(0, (a, c) => a + c.Seconds));
            Console.WriteLine("Department calls: ");
            Show(calls);
        }

        private void Homework4() {
            // Show the departments with the youngest employee, 
            // together with the name of the youngest employee and his/her age 
            // (more than one youngest employee may exist)
            var deps = model.Employees.GroupBy(e => e.Department.Name,
                (dep, empl) => new
                {
                    DepName = dep,
                    Empleados = empl,
                    MinAge = empl.Select(e => e.Age).Min()
                }).Select(d => $"Department = {d.DepName}, Empleado = {d.Empleados.First(e => e.Age.Equals(d.MinAge)).Name}, Edad = {d.MinAge}");
            Show(deps);
        }

        private void Homework5() {
            // Show the greatest summation of phone call durations, in seconds, 
            // of the employees in the same department, together with the name of the department 
            // (it can be assumed that there is only one department fulfilling that condition)
            var res = model.Employees
                .Join(model.PhoneCalls,
                e => e.TelephoneNumber,
                c => c.SourceNumber,
                (e, c) => new
                {
                    Department = e.Department,
                    Duration = c.Seconds
                }).GroupBy(e => e.Department, (a, b) => new
                {
                    name = a.Name,
                    duration = b.Aggregate(0, (a, c) => a + c.Duration)
                });
            Show(res);
        }


    }

}
