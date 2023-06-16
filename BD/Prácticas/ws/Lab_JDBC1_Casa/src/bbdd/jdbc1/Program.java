package bbdd.jdbc1;
import java.awt.Taskbar.State;
import java.sql.*;
import java.util.Scanner;

public class Program {
	
	private static String USERNAME = "UO289097";
	private static String PASSWORD = "passUO289097";
	private static String CONNECTION_STRING = "jdbc:oracle:thin:@156.35.94.98:3389:desa19";
	
	public static void main(String[] args) {
//		exercise1_1();
//		exercise1_2();
//		exercise2();
//		exercise3();
//		exercise4();
		try {
//			exercise6_1();
//			exercise6_2();
//			exercise1_1();
//			exercise7_2();
			procedure10();
//			exercise8();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	/*
		1.	Crear un metodo en Java que muestre por pantalla los resultados de las consultas 21 y 32 
		de la Practica SQL2. 
		1.1. (21) Obtener el nombre y el apellido de los clientes que han adquirido un coche en un 
		concesionario de Madrid, el cual dispone de coches del modelo gti.
	 */
	public static void exercise1_1() throws SQLException {
		System.out.println("########### EJERCICIO 1.1 ###########");
		Connection con = getConnection();
		
		StringBuilder query = new StringBuilder();
		query.append("select c.nombre, c.apellido \r\n"
				+ "from clientes c\r\n"
				+ "where c.dni in (select DISTINCT v.dni \r\n"
				+ "from ventas v, coches CH, concesionarios CO, distribucion D \r\n"
				+ "where V.cifc=CO.cifc AND CO.cifc = D.cifc AND D.codcoche = CH.codcoche\r\n"
				+ "AND CH.modelo = 'gti')");
		
		Statement st = con.createStatement();
		ResultSet rs = st.executeQuery(query.toString());
//		showResults(rs);
		while(rs.next()) {
			System.out.println(rs.getString(1) + "\t" + rs.getString(2));
		}
		
		rs.close();
		st.close();
		con.close();
	}
	
	/* 
		1.2. (32) Obtener un listado de los concesionarios cuyo promedio de coches supera a 
		la cantidad promedio de todos los concesionarios. 
	*/
	public static void exercise1_2() {
		
	}
	
	/*
		2. Crear un metodo en Java que muestre por pantalla el resultado de la consulta 6 de la Practica SQL2 de forma el color de la busqueda sea introducido por el usuario.
			(6) Obtener el nombre de las marcas de las que se han vendido coches de un color 
			introducido por el usuario.
	*/
	public static void exercise2() throws SQLException {
		System.out.println("########### EJERCICIO 1.1 ###########");
		Connection con = getConnection();
		
		String color = ReadString();
		
		StringBuilder query = new StringBuilder();
		query.append("select m.nombrem \r\n"
				+ "from marcas m, marco r, coches c, ventas v\r\n"
				+ "where m.cifm = r.cifm and r.codcoche = c.codcoche\r\n"
				+ "and c.codcoche = v.codcoche and v.color = ?");
		
		
		PreparedStatement ps = con.prepareStatement(query.toString());
		ps.setString(1, color);
		ResultSet rs = ps.executeQuery();
		showResults(rs);
		
		ps.close();
		rs.close();
		con.close();
	}
	
	/*
		3.	Crear un metodo en Java para ejecutar la consulta 27 de la Practica SQL2 de forma que los limites la cantidad de coches sean introducidos por el usuario. 
			(27) Obtener el cifc de los concesionarios que disponen de una cantidad de coches comprendida entre dos cantidades introducidas por el usuario, ambas inclusive.

	*/
	public static void exercise3() {
		
	}
	
	/*
		4.	Crear un metodo en Java para ejecutar la consulta 24 de la Practica SQL2 de forma que tanto la ciudad del concesionario como el color sean introducidos por el usuario. 
			(24) Obtener los nombres de los clientes que no han comprado coches de un color introducido por el usuario en concesionarios de una ciudad introducida por el usuario.

	*/
	public static void exercise4() {
		
	}
	
	/*
		5.	Crear un metodo en Java que haciendo uso de la instruccion SQL adecuada: 
		5.1. Introduzca datos en la tabla coches cuyos datos son introducidos por el usuario.

	*/
	public static void exercise5_1() {
		
	}
	
	/*
		5.2. Borre un determinado coche cuyo codigo es introducido por el usuario. 
	*/
	public static void exercise5_2() {
		
	}
	
	/*	 
		5.3. Actualice el nombre y el modelo para un determinado coche cuyo codigo es introducido por el usuario.
	*/
	public static void exercise5_3() {		
		
	}
	
	/*
		6. Invocar la funcion y el procedimiento del ejercicio 10 de la practica PL1 desde una aplicacion Java. 
			(10) Realizar un procedimiento y una funcion que dado un codigo de concesionario devuelve el numero ventas que se han realizado en el mismo.
		6.1. Funcion
	*/
	public static void exercise6_1() throws SQLException {		
		Connection con = getConnection();
		
		StringBuilder query = new StringBuilder();
		query.append("{? = call FUNCTION10(?)}");
		
		CallableStatement cst = con.prepareCall(query.toString());
		cst.registerOutParameter(1, Types.INTEGER);
		cst.setInt(2, 1);
		cst.execute();
		System.out.println(cst.getInt(1));
		
		cst.close();
		con.close();
		
	}
	
	/*	
		6.2. Procedimiento
	*/
	public static void exercise6_2() throws SQLException {		
		Connection con = getConnection();
		
		StringBuilder query = new StringBuilder();
		query.append("{ call PROCEDURE_10(?,?)}");
		
		CallableStatement cst = con.prepareCall(query.toString());
		cst.setInt(1, 1);
		cst.registerOutParameter(2, Types.INTEGER);
		cst.execute();
		
		System.out.println(cst.getInt(2));
		
		cst.close();
		con.close();
	}
	
	/*
		7. Invocar la funcion y el procedimiento del ejercicio 11 de la Practica PL1 desde una aplicacion Java. 
			(11) Realizar un procedimiento y una funcion que dada una ciudad que se le pasa como parametro devuelve el numero de clientes de dicha ciudad.
		7.1. Funcion

	*/
	public static void exercise7_1() {		
			
	}	
	
	/*
		7.2. Procedimiento
	*/
	public static void exercise7_2() throws SQLException {		
		Connection con = getConnection();	
		
		StringBuilder query = new StringBuilder();
		query.append("{call PROCEDURE8_I()}");
		
		CallableStatement cs = con.prepareCall(query.toString());
		cs.execute();
		
		
	}
	
	public static void procedure10() throws SQLException {
		Connection con = getConnection();
		
		StringBuilder query = new StringBuilder();
		query.append("{call PROCEDURE_10(?,?)}");
		
		CallableStatement cs = con.prepareCall(query.toString());
		
		cs.setInt(1, 3);
		cs.registerOutParameter(2, Types.INTEGER);
		
		cs.execute();
		
		System.out.print(cs.getInt(2));
	}
	
    /*
     	8. Crear un m�todo en Java que imprima por pantalla los coches que han sido adquiridos por cada cliente.
     	Ademas, debera imprimirse para cada cliente el numero de coches que ha comprado y el numero de
     	concesionarios en los que ha comprado. Aquellos clientes que no han adquirido ningun coche no
		deben aparecer en el listado.
    */
	public static void exercise8() throws SQLException {		
		Connection con = getConnection();
		
		StringBuilder clientes = new StringBuilder();
		clientes.append("select distinct c.dni, c.nombre, c.apellido from clientes c, ventas v where c.dni = v.dni");
		Statement stClientes = con.createStatement();
		ResultSet rsClientes = stClientes.executeQuery(clientes.toString());
		
		StringBuilder numeros = new StringBuilder();
		numeros.append("select count(codcoche), count(DISTINCT cifc) from ventas v "
				+ "where v.dni = ? ");
		PreparedStatement pstNumeros = con.prepareStatement(numeros.toString());
		
		StringBuilder coches = new StringBuilder();
		coches.append("select c.codcoche, c.nombrech, c.modelo, v.color from coches c, ventas v "
				+ "where v.dni = ? and c.codcoche = v.codcoche");
		PreparedStatement pstCoches = con.prepareStatement(coches.toString());
		
		while(rsClientes.next()) {
			pstNumeros.setString(1, rsClientes.getString(1));
			ResultSet rsNumeros = pstNumeros.executeQuery();
			rsNumeros.next();
			
			System.out.println("- Cliente: " + rsClientes.getString(2) + " " + rsClientes.getString(3) + " "
					+ rsNumeros.getInt(1) + " " + rsNumeros.getInt(2));
			
			pstCoches.setString(1, rsClientes.getString(1));
			ResultSet rsCoches = pstCoches.executeQuery();
			
			while(rsCoches.next()) {
				//Imprimes la paranoia
				System.out.println("---> Coche: " + rsCoches.getString(1) + " " + rsCoches.getString(2) + " "
						+ rsCoches.getString(3) + " " + rsCoches.getString(4));
			}
			
			rsCoches.close();
			rsNumeros.close();
		}
		pstCoches.close();
		pstNumeros.close();
		rsClientes.close();
		stClientes.close();
		con.close();
		
	}
	
	/*
    Realizar un listado en el que, para los cines de una determinada localidad, se indique la recaudacion total
	obtenida en cada cine, asi como la obtenida por cada una de las peliculas en el proyectadas
    	Cine 1 - Recaudacion_total
			Codpelicula1 - Titulo1- Recaudacion_total_pelicula_1_en_cine1
			Codpelicula 2 - Titulo2 - Recaudacion_total_pelicula_2_en_cine1
		Cine 2 – Recaudacion_total
			Codpelicula1 – Titulo1 – Recaudacion_total_pelicula_1_en_cine2
			Codpelicula 2 – Titulo2 – Recaudacion_total_pelicula_2_en_cine2
			Codpelicula 3 – Titulo3 – Recaudacion_total_pelicula_3_en_cine2 
    */
	public static void exercise8_b() throws SQLException {
		Connection con = getConnection();
		System.out.println("EJERCICIO 8  B");
		
		StringBuilder cine =new StringBuilder();
		cine.append("select c.codcine, sum(precio) from cines c, salas s, entradas e "
				+ "where c.codcine = s.codcine and s.codsala = e.codsala \r\n"
				+ "group by c.codcine");
		Statement stCines = con.createStatement();
		ResultSet rsCines = stCines.executeQuery(cine.toString());
		
		StringBuilder peliculas = new StringBuilder();
		peliculas.append("select p.codpelicula, p.titulo, sum(precio) from peliculas p, salas s, entradas e \r\n"
				+ "where s.codsala = e.codsala and p.codpelicula = e.codpelicula and s.codcine = ? \r\n"
				+ "group by p.codpelicula, p.titulo");
		PreparedStatement pstPeliculas = con.prepareStatement(peliculas.toString());
		
		while(rsCines.next()) {
			pstPeliculas.setString(1, rsCines.getString(1));
			ResultSet rsPeliculas = pstPeliculas.executeQuery();
			//Imprime la paranoia
			
			while(rsPeliculas.next()) {
				//Imprime la paranoia
			}
		}
		
		//Cierra la paranoia
	}
	
	/*
	En JAVA:
	a. Realizar un listado en el que se indique la siguiente informacion para cada pelicula:
		Titulo_Pelicula 1
			Cine 1
				Sala - Sesion - Numero de espectadores
				Sala - Sesion - Numero de espectadores
			Cine 2
				Sala - Sesion - Numero de espectadores
				Sala - Sesion - Numero de espectadores
	*/
	public static void exercise8_c() throws SQLException {
		System.out.println("########### EJERCICIO 8.C ###########");
		Connection con = getConnection();
		
		StringBuilder peliculas = new StringBuilder();
		peliculas.append("");
	}
	
	private static Connection getConnection() throws SQLException{
		if(DriverManager.getDriver(CONNECTION_STRING) == null) {
			if(CONNECTION_STRING.contains("oracle")) {
				DriverManager.registerDriver(new oracle.jdbc.OracleDriver());
			}else { 
				DriverManager.registerDriver(new org.hsqldb.jdbc.JDBCDriver());
			}
		}
		return DriverManager.getConnection(CONNECTION_STRING, USERNAME, PASSWORD);
	}
	
	private static void showResults(ResultSet rs) throws SQLException{
		int columnCount = rs.getMetaData().getColumnCount();
		StringBuilder headers = new StringBuilder();
		
		for(int i = 1; i < columnCount; i++) {
			headers.append(rs.getMetaData().getColumnName(i) + "\t");
		}
		headers.append(rs.getMetaData().getColumnName(columnCount));
		
		System.out.println(headers.toString());
		StringBuilder result = null;
		
		while(rs.next()) {
			result = new StringBuilder();
			for(int i = 1; i < columnCount; i++) {
				result.append(rs.getObject(i) + "\t");
			}
			result.append(rs.getObject(columnCount));
			System.out.println(result.toString());
		}
		
		if(result == null) {
			System.out.println("No se encontraron datos");
		}
	}
		
	@SuppressWarnings("resource")
	private static String ReadString(){
		return new Scanner(System.in).nextLine();		
	}
	
	@SuppressWarnings("resource")
	private static int ReadInt(){
		return new Scanner(System.in).nextInt();			
	}	
}
