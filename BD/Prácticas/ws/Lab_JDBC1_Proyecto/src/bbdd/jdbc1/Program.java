package bbdd.jdbc1;
import java.util.Scanner;
import java.sql.*;

public class Program {
	
	private static String USERNAME = "UO289097";
	private static String PASSWORD = "passUO289097";
	private static String CONNECTION_STRING = "jdbc:oracle:thin:@156.35.94.98:3389:desa19";
	
	public static void main(String[] args) {
//		//Ejemplos para leer por teclado
//		System.out.println("Leer un entero por teclado");	
//		int entero = ReadInt();
//		System.out.println("Leer una cadena por teclado");	
//		String cadena = ReadString();
		try {
//			exercise1_1();
//			exercise1_2();
//			exercise2();
//			exercise3();
//			exercise4();
//			executeUpdate para insertar, eliminar y actualizar
//			exercise5_1();
//			exercise5_2();
//			exercise5_3();
//			exercise6_1();
//			exercise6_2();
//			exercise7_1();
//			exercise7_2();
			exercise8();
//			exercise8_b();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	/*
		1.	Crear un metodo en Java que muestre por pantalla los resultados de las consultas 21 y 32 de la Practica SQL2. 
		1.1. (21) Obtener el nombre y el apellido de los clientes que han adquirido un coche en un concesionario de Madrid, el cual dispone de coches del modelo gti.
	 */
	public static void exercise1_1() throws SQLException {
		System.out.println("########### EJERCICIO 1.1 ###########");
		Connection con = getConnection();
		
		StringBuilder query = new StringBuilder();
		query.append("Select nombre, apellido ");
		query.append("FROM clientes ");
		query.append("where dni IN (");
		query.append("SELECT DISTINCT V.dni ");
		query.append("FROM ventas V, coches CH, concesionarios CO, distribucion D ");
		query.append("	WHERE V.cifc=CO.cifc ");
		query.append("	AND CO.cifc = D.cifc");
		query.append("	AND D.codcoche = CH.codcoche");
		query.append("	AND CH.modelo = 'gti'");
		query.append(")");
		
		Statement st = con.createStatement();
		ResultSet rs = st.executeQuery(query.toString());
		showResults(rs);
		
		rs.close();
		con.close();
		st.close();
	}
	
	/* 
		1.2. (32) Obtener un listado de los concesionarios cuyo promedio de coches supera a la cantidad promedio de todos los concesionarios. 
	*/
	public static void exercise1_2() throws SQLException {
		System.out.println("\n########### EJERCICIO 1.2 ###########");
		Connection con = getConnection();
		
		StringBuilder query = new StringBuilder();
		query.append("SELECT cifc,nombrec,ciudadc");
		query.append(" FROM concesionarios");
		query.append(" WHERE cifc IN(");
		query.append(" SELECT cifc");
		query.append(" FROM distribucion GROUP BY cifc");
		query.append(" HAVING SUM(cantidad)> (SELECT AVG(total)"
				+ " FROM(SELECT SUM(cantidad)total FROM distribucion GROUP BY cifc)))");
		
		Statement st = con.createStatement();
		ResultSet rs = st.executeQuery(query.toString());
		showResults(rs);
		
		rs.close();
		st.close();
		con.close();
	}
	
	/*
		2. Crear un metodo en Java que muestre por pantalla el resultado de la consulta 6 de la Practica SQL2 de forma el color de la busqueda sea introducido por el usuario.
			(6) Obtener el nombre de las marcas de las que se han vendido coches de un color introducido por el usuario.
	*/
	public static void exercise2() throws SQLException {
		System.out.println("\n########### EJERCICIO 2 ###########");
		Connection con = getConnection();
		
		System.out.print("Escriba un color: ");	
		String color = ReadString();
		
		StringBuilder query = new StringBuilder();
		query.append("SELECT DISTINCT M.nombrem");
		query.append("FROM marcas M, marco R, ventas V");
		query.append("WHERE M.cifm=R.cifm AND R.codcoche=V.codcoche AND V.color= ?");
		
		PreparedStatement pst = con.prepareStatement(query.toString());
		pst.setString(1, color.toLowerCase());
		ResultSet rs = pst.executeQuery();
		showResults(rs);
		
		rs.close();
		pst.clearBatch();
		pst.close();
		con.close();
	}
	
	/*
		3.	Crear un metodo en Java para ejecutar la consulta 27 de la Practica SQL2 de forma que los limites la cantidad de coches 
		sean introducidos por el usuario. 
		(27) Obtener el cifc de los concesionarios que disponen de una cantidad de coches comprendida entre dos cantidades 
		introducidas por el usuario, ambas inclusive.

	*/
	public static void exercise3() throws SQLException {
		System.out.println("\n########### EJERCICIO 3 ###########");
		Connection con = getConnection();
		
		System.out.print("Escriba límite inferior: ");	
		int limInf = ReadInt();
		
		System.out.print("Escriba límite superior: ");	
		int limSup = ReadInt();
		
		StringBuilder query = new StringBuilder();
		query.append("SELECT cifc, sum(cantidad) AS total\r\n"
				+ "FROM distribucion\r\n"
				+ "GROUP BY cifc\r\n"
				+ "HAVING sum(cantidad) BETWEEN ? AND ?");
		
		PreparedStatement pst = con.prepareStatement(query.toString());
		pst.setInt(1, limInf);
		pst.setInt(2, limSup);
		ResultSet rs = pst.executeQuery();
		showResults(rs);
		
		rs.close();
		pst.clearBatch();
		pst.close();
		con.close();
	}
	
	/*
		4.	Crear un metodo en Java para ejecutar la consulta 24 de la Practica SQL2 de forma que 
		tanto la ciudad del concesionario como el color sean introducidos por el usuario. 
			(24) Obtener los nombres de los clientes que no han comprado coches de un color 
			introducido por el usuario en concesionarios de una ciudad introducida por el usuario.

	*/
	public static void exercise4() throws SQLException {
		System.out.println("\n########### EJERCICIO 4 ###########");
		Connection con = getConnection();
		
		System.out.print("Escriba la ciudad: ");	
		String ciudad = ReadString();
		
		System.out.print("Escriba el color: ");	
		String color = ReadString();
		System.out.print("\n");
		
		StringBuilder query = new StringBuilder();
		query.append("SELECT DISTINCT CL.nombre\r\n"
				+ "FROM clientes CL, ventas V\r\n"
				+ "WHERE V.dni=CL.dni AND CL.dni NOT IN (SELECT V.dni\r\n"
				+ "    FROM concesionarios CO, ventas V\r\n"
				+ "    WHERE CO.cifc=V.cifc AND CO.ciudadc=? AND V.color=?)");
		
		PreparedStatement pst = con.prepareStatement(query.toString());
		pst.setString(1, ciudad.toLowerCase());
		pst.setString(2, color.toLowerCase());
		ResultSet rs = pst.executeQuery();
		showResults(rs);
		
		rs.close();
		pst.clearBatch();
		pst.close();
		con.close();
	}
	
	/*
		5.	Crear un metodo en Java que haciendo uso de la instruccion SQL adecuada: 
		5.1. Introduzca datos en la tabla coches cuyos datos son introducidos por el usuario.

	*/
	public static void exercise5_1() throws SQLException {
		System.out.println("\n########### EJERCICIO 5.1 ###########");
		Connection con = getConnection();
		
		System.out.print("Escriba el código del coche: ");	
		int codCoche = ReadInt();
		
		System.out.print("Escriba el nombre del coche: ");
		String nombre = ReadString();
		
		System.out.print("Escriba el modelo del coche: ");
		String modelo = ReadString();
		
		StringBuilder query = new StringBuilder();
		query.append("INSERT INTO coches (codcoche, nombrech, modelo) VALUES (?,?,?)");
		
		PreparedStatement pst = con.prepareStatement(query.toString());
		pst.setInt(1, codCoche);
		pst.setString(2, nombre);
		pst.setString(3, modelo);
		
		if(pst.executeUpdate() == 1)
			System.out.println("Datos insertados correctamente");
		else
			System.out.println("Datos no insertados");
		
		pst.clearBatch();
		pst.close();
		con.close();
		
	}
	
	/*
		5.2. Borre un determinado coche cuyo codigo es introducido por el usuario. 
	*/
	public static void exercise5_2() throws SQLException {
		System.out.println("\n########### EJERCICIO 5.2 ###########");
		Connection con = getConnection();
		
		System.out.print("Escriba el código del coche: ");	
		int codCoche = ReadInt();
		
		System.out.print("\n");
		StringBuilder query = new StringBuilder();
		query.append("Delete from coches c where c.codcoche = ?");
		
		PreparedStatement pst = con.prepareStatement(query.toString());
		pst.setInt(1, codCoche);
		if(pst.executeUpdate() == 1) 
			System.out.println("Coche borrado correctamente");
		else
			System.out.println("Coche no borrado");
		
		pst.close();
		con.close();
	}
	
	/*	 
		5.3. Actualice el nombre y el modelo para un determinado coche cuyo codigo es introducido por el usuario.
	*/
	public static void exercise5_3() throws SQLException {		
		System.out.println("\n########### EJERCICIO 5.3 ###########");
		Connection con = getConnection();
		
		System.out.print("Escriba el código del coche: ");	
		int codCoche = ReadInt();
		
		System.out.print("Escriba el nombre del coche: ");
		String nombre = ReadString();
		
		System.out.print("Escriba el modelo del coche: ");
		String modelo = ReadString();
		
		System.out.print("\n");
		StringBuilder query = new StringBuilder();
		query.append("UPDATE coches c SET c.nombrech = ?, c.modelo = ? where c.codcoche = ?");
		
		
		PreparedStatement pst = con.prepareStatement(query.toString());
		pst.setString(1, nombre);
		pst.setString(2, modelo);
		pst.setInt(3, codCoche);
		
		if(pst.executeUpdate() == 1) 
			System.out.println("Coche actualizado correctamente");
		else
			System.out.println("Coche no actualizado");
		
		pst.close();
		con.close();
	}
	
	/*
		6. Invocar la funcion y el procedimiento del ejercicio 10 de la practica PL1 desde una aplicacion Java. 
			(10) Realizar un procedimiento y una funcion que dado un codigo de concesionario devuelve el numero 
			ventas que se han realizado en el mismo.
		6.1. Funcion
	*/
	public static void exercise6_1() throws SQLException {		
		System.out.println("\n########### EJERCICIO 6.1 ###########");
		Connection con = getConnection();
		
		StringBuilder query = new StringBuilder();
		query.append("{? = call FUNCTION10(?)}");
		
		System.out.println("Escriba el código del concesionario: ");
		String cifc = ReadString();
		
		CallableStatement cst = con.prepareCall(query.toString());
		cst.registerOutParameter(1, Types.INTEGER, 0);
		cst.setString(2, cifc);
		
		cst.execute();
		System.out.println("Ventas: " + cst.getInt(1));
		
		cst.close();
		con.close();
	}
	
	/*	
		6.2. Procedimiento
	*/
	public static void exercise6_2() throws SQLException {		
		System.out.println("\n########### EJERCICIO 6.2 ###########");
		Connection con = getConnection();
		
		System.out.print("Escriba el código del concesionario: ");
		String cifc = ReadString();
		
		StringBuilder query = new StringBuilder();
		query.append("{call PROCEDURE_10(?,?)}");
		
		CallableStatement cst = con.prepareCall(query.toString());
		cst.setString(1, cifc);
		cst.registerOutParameter(2, Types.INTEGER);
		
		cst.execute();
		System.out.println("Ventas: " + cst.getInt(2));
		
		cst.close();
		con.close();
		
	}
	
	/*
		7. Invocar la funcion y el procedimiento del ejercicio 11 de la Practica PL1 desde una aplicacion Java. 
			(11) Realizar un procedimiento y una funcion que dada una ciudad que se le pasa como parametro 
			devuelve el numero de clientes de dicha ciudad.
		7.1. Funcion

	*/
	public static void exercise7_1() throws SQLException {		
		System.out.println("\n########### EJERCICIO 6.2 ###########");
		Connection con = getConnection();
		
		StringBuilder query = new StringBuilder();
		query.append("{? = call FUNCTION11(?)}");
		
		System.out.println("Escriba la ciudad: ");
		String ciudad = ReadString();
		
		CallableStatement cst = con.prepareCall(query.toString());
		cst.registerOutParameter(1, Types.INTEGER, 0);
		cst.setString(2, ciudad.toLowerCase());
		
		cst.execute();
		System.out.println("Número de clientes: " + cst.getInt(1));
		
		cst.close();
		con.close();
	}	
	
	/*
		7.2. Procedimiento
	*/
	public static void exercise7_2() throws SQLException {		
		System.out.println("\n########### EJERCICIO 6.2 ###########");
		Connection con = getConnection();
		
		System.out.print("Escriba la ciudad: ");
		String ciudad = ReadString();
		
		StringBuilder query = new StringBuilder();
		query.append("{call PROCEDURE_11(?,?)}");
		
		CallableStatement cst = con.prepareCall(query.toString());
		cst.setString(1, ciudad);
		cst.registerOutParameter(2, Types.INTEGER);
		
		cst.execute();
		System.out.println("Número de clientes: " + cst.getInt(2));
		
		cst.close();
		con.close();
	}
	
    /*
     	8. Crear un metodo en Java que imprima por pantalla los coches que han sido adquiridos por cada cliente.
     	Ademas, debera imprimirse para cada cliente el numero de coches que ha comprado y el numero de
     	concesionarios en los que ha comprado. Aquellos clientes que no han adquirido ningun coche no
		deben aparecer en el listado.
    */
	public static void exercise8() throws SQLException {		
		System.out.println("########### EJERCICIO 8 ###########");
		Connection con = getConnection();
		
		StringBuilder query = new StringBuilder();
		query.append("SELECT distinct c.dni, nombre, apellido from clientes c, ventas v where c.dni = v.dni");
		Statement st = con.createStatement();
		ResultSet rsClientes = st.executeQuery(query.toString());
		
		//Obtener numero de coches comprados y numconcesionarios parámetro dni
		StringBuilder queryCount = new StringBuilder();
		queryCount.append("select count(*) as numcoches, COUNT(DISTINCT cifc) as numconc from ventas where dni = ?");
		PreparedStatement pstCounts = con.prepareStatement(queryCount.toString());
//		pstCounts.setInt(1, rs.getInt(0));
		
		//Datos de los coches comprados con parámetro dni
		StringBuilder queryCoches = new StringBuilder();
		queryCoches.append("select c.codcoche, c.nombrech,c.modelo, v.color from coches c, ventas v");
		queryCoches.append(" where v.codcoche = c.codcoche and v.dni = ?");
		PreparedStatement pstCars = con.prepareStatement(queryCoches.toString());
//		pstCars.setInt(1, rs.getInt(0));
		
		while(rsClientes.next()) {
			pstCounts.setString(1, rsClientes.getString("dni"));
			ResultSet rs = pstCounts.executeQuery();
			rs.next();
			
			System.out.println("- Cliente: " + rsClientes.getString("nombre") + " " + rsClientes.getString("apellido")
			+ " " + rs.getInt("numcoches") + " " + rs.getInt("numconc"));
			
			pstCars.setString(1, rsClientes.getString("dni"));
			rs = pstCars.executeQuery();
			
			while(rs.next()) {
				System.out.println("---> Coche: "+ rs.getString("codcoche") + " " + rs.getString("nombrech") 
				+ " " + rs.getString("modelo") + " " + rs.getString("color"));
			}
			rs.close();
		}
		
		pstCounts.close();
		pstCars.close();
		rsClientes.close();
		st.close();
		con.close();
	}
	
	/*
    Realizar un listado en el que, para los cines de una determinada localidad, se indique la recaudacion total
	obtenida en cada cine, asi como la obtenida por cada una de las peliculas en el proyectadas
    	Cine 1 - Recaudacion_total
			Codpelicula1 - Titulo1- Recaudacion_total_pelicula_1_en_cine1
			Codpelicula 2 - Titulo2 - Recaudacion_total_pelicula_2_en_cine1
		Cine 2 â€“ Recaudacion_total
			Codpelicula1 â€“ Titulo1 â€“ Recaudacion_total_pelicula_1_en_cine2
			Codpelicula 2 â€“ Titulo2 â€“ Recaudacion_total_pelicula_2_en_cine2
			Codpelicula 3 â€“ Titulo3 â€“ Recaudacion_total_pelicula_3_en_cine2 
    */
	public static void exercise8_b() throws SQLException {
		System.out.println("########### EJERCICIO 8.B ###########");
		Connection con = getConnection();
		
		System.out.print("Escriba la localidad: ");
		String localidad =ReadString();
		
		StringBuilder queryCine = new StringBuilder();
		queryCine.append("SELECT c.codcine, sum(precio) recaudacion_cine ");
		queryCine.append("FROM cines c, salas s, entradas e ");
		queryCine.append("WHERE c.codcine=s.codcine AND s.codsala=e.codsala AND c.localidad= ? ");
		queryCine.append("GROUP BY c.codcine");
		PreparedStatement pstCine = con.prepareStatement(queryCine.toString());
		pstCine.setString(1, localidad);
		
		StringBuilder queryPelicula = new StringBuilder();
		queryPelicula.append("SELECT p.codpelicula, p.titulo, sum(precio) recaudacion_peli\r\n"
				+ " FROM peliculas p, entradas e, salas s \r\n"
				+ " WHERE p.codpelicula=e.codpelicula AND e.codsala=s.codsala AND s.codcine= ? \r\n"
				+ " GROUP BY p.codpelicula, p.titulo");
		PreparedStatement pstPelicula = con.prepareStatement(queryPelicula.toString());
		ResultSet rs = pstCine.executeQuery();
		
		while(rs.next()) {
			System.out.println("Cine " + rs.getString(1) + " " + rs.getString(2));
			rs.next();
			
			pstPelicula.setString(1, rs.getString(1));
			ResultSet rsPel = pstPelicula.executeQuery();
			while(rsPel.next()) {
				System.out.println("  " + rsPel.getString(1) + " - " + rsPel.getString(2) + " - " + rsPel.getString(3));
			}
		}
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
		
		StringBuilder queryPelicula = new StringBuilder();
		queryPelicula.append("SELECT codpelicula, titulo");
		queryPelicula.append(" FROM peliculas");
		Statement st = con.createStatement();
		ResultSet rsPeliculas = st.executeQuery(queryPelicula.toString());
		
		StringBuilder queryCine = new StringBuilder();
		queryCine.append("SELECT DISTINCT s.codcine ");
		queryCine.append(" FROM salas s, proyectan p ");
		queryCine.append(" WHERE s.codsala=p.codsala AND codpelicula= ?");
		PreparedStatement pstCine = con.prepareStatement(queryCine.toString());
		
		StringBuilder querySala = new StringBuilder();
		querySala.append("SELECT s.codsala, sesion, sum(entradasvendidas) AS ev ");
		querySala.append(" FROM proyectan p, salas s ");
		querySala.append(" WHERE p.codsala=s.codsala AND codpelicula= ? AND codcine = ?");
		querySala.append(" GROUP BY s.codsala, sesion");
		PreparedStatement pstSala = con.prepareStatement(querySala.toString());
		
		while(rsPeliculas.next()) {
			pstCine.setString(1, rsPeliculas.getString(1));
			System.out.println(rsPeliculas.getString(1));
			
			ResultSet rsCine = pstCine.executeQuery();
			pstSala.setString(1, rsPeliculas.getString(1));
			pstSala.setString(2, rsCine.getString(1));
			
			while(rsCine.next()) {
				System.out.println("  " + rsCine.getString(1));
			}
			
			
		}
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
