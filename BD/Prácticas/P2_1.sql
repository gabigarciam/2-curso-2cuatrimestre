/*Ejercicio 1*/
select * from marcas where ciudadm = 'barcelona';
/*Ejercicio 2a*/
select * from clientes where (ciudad = 'madrid' and apellido = 'garcia');
/*Ejercicio 2a*/
select * from clientes where (ciudad = 'madrid' or apellido = 'garcia');
/*Ejercicio 3*/
select apellido, ciudad from clientes;
/*Ejercicio 4*/
select apellido from clientes where ciudad = 'madrid';
/*Ejercicio 5*/
select distinct nombrem from marcas m, marco ma, coches c where
(m.cifm = ma.cifm and ma.codcoche = c.codcoche and c.modelo = 'gtd');
/*Ejercicio 6*/
select distinct nombrem from marcas m, marco ma, coches c, ventas v 
where (m.cifm = ma.cifm and ma.codcoche = v.codcoche and v.color = 'rojo'); 
/*Ejercicio 7*/
SELECT nombrech from coches 
WHERE modelo IN (select modelo from coches where nombrech = 'cordoba');
/*Ejercicio 8*/
select distinct nombrech from coches 
where modelo not in (select modelo from coches where modelo = 'gtd');
/*Ejercicio 9*/
SELECT * FROM concesionarios;
/*Ejercicio 10*/
select m.cifm, c.dni from marcas m, clientes c 
where m.ciudadm = c.ciudad;
/*Ejercicio 11: Obtener los valores del atributo codcoche para los coches que se encuentran en algún
concesionario de ‘barcelona’*/
select d.codcoche from distribucion d, concesionarios c
where (d.cifc = c.cifc and c.ciudadc = 'barcelona');
/*Ejercicio 12: Obtener los valores del atributo codcoche para los coches que han sido adquiridos por un
cliente de ‘madrid’ en un concesionario de ‘madrid’*/
select h.codcoche from concesionarios c, clientes l, ventas v, coches h
where (l.ciudad = 'madrid' and l.ciudad = c.ciudadc and l.dni = v.dni 
and v.cifc = c.cifc and v.codcoche = h.codcoche);
/*Ejercicio 13: Obtener los valores del atributo codcoche para los coches comprados 
en un concesionario de la misma ciudad que la del cliente que lo compra. */
select c.codcoche from coches c, ventas v, concesionarios r, clientes l
where (l.ciudad = r.ciudadc and v.codcoche = c.codcoche and v.cifc = r.cifc 
and l.dni = v.dni);
/*Ejercicio 14: Obtener todas las parejas de nombres de marcas que sean 
de la misma ciudad.*/
select m.nombrem, r.nombrem from marcas m, marcas r 
where m.ciudadm = r.ciudadm and m.nombrem != r.nombrem;
/*Ejercicio 15: Obtener todas las tuplas de la relación clientes 
correspondientes a clientes de ‘madrid’*/
SELECT * FROM clientes where ciudad = 'madrid';
/*Ejercicio 16: Obtener el dni de los clientes que han comprado 
algún coche en un concesionario de ‘madrid’*/
select distinct c.dni from ventas v, clientes c, concesionarios r
where(c.dni = v.dni and r.cifc = v.cifc and r.ciudadc = 'madrid' );
/*Ejercicio 17: Obtener los colores de los coches vendidos 
por el concesionario ‘acar’*/
select v.color from ventas v, concesionarios c 
where (v.cifc = c.cifc and c.nombrec = 'acar');
/*Ejercicio 18: Obtener los valores del atributo codcoche para 
los coches vendidos por algún concesionario de ‘madrid’*/
select c.codcoche from coches c, ventas v, concesionarios r 
where (c.codcoche = v.codcoche and v.cifc = r.cifc and r.ciudadc = 'madrid' );
/*Ejercicio 19: Obtener todos los nombres de los clientes que hayan 
adquirido algún coche en el concesionario ‘dcar’*/
select c.nombre from clientes c, concesionarios r, ventas v
where (c.dni = v.dni and v.cifc = r.cifc and r.nombrec = 'dcar');
/*Ejercicio 20: Obtener el nombre y el apellido de los clientes 
que han adquirido un coche modelo ‘gti’ de color ‘blanco’*/
select c.nombre, c.apellido from clientes c, ventas v, coches h
where (c.dni = v.dni and h.codcoche = v.codcoche and h.modelo = 'gti' 
and v.color = 'blanco');
/*Ejercicio 21: Obtener el nombre y el apellido de los clientes que 
han adquirido un automóvil en un concesionario de ‘madrid’ 
que dispone de coches del modelo ‘gti’*/
select c.nombre, c.apellido from clientes c
where c.dni in (SELECT DISTINCT V.dni
    FROM ventas V, coches CH, concesionarios CO, distribucion D
    WHERE V.cifc=CO.cifc AND CO.ciudadc='madrid' AND CO.cifc=D.cifc
        AND D.codcoche = CH.codcoche AND CH.modelo='gti');
/*P7=====================*/
/*Ejercicio 1: Obtener el nombre de las estaciones y su número 
de transformadores,  para las estaciones en las que alguna de las centrales 
nucleares que les entregan energía genera más de 25000 residuos*/
select e.enombre, e.transformadores from estacion e, entrega g, nuclear n
where e.enombre = g.enombre and g.pnombre = n.pnombre and n.residuos > 25000;
/*Obtener el nombre de las compañías que comienza por la letra ‘C’ 
que poseen redes de distribución que envían energía a otras redes, 
pero no reciben energía de ninguna otra red*/
select distinct c.cnombre from compania c, red_distribucion r, red_distribucion d 
WHERE c.cnombre LIKE 'C%' 
and r.numred in (select e.numred_envia from envia_energia e) 
and r.numred not in (SELECT e.numred_recibe from envia_energia e);
/*Ejercicio 3: Obtener para cada envío de energía entre redes de distribución, el número de red de la red
que envía energía y de la que la recibe, así como el volumen de energía del envío siempre y
cuando la estación de cabecera de la red que envía energía tenga un número de
transformadores mayor que el número de transformadores de la red que recibe la energía y
el volumen de energía enviado sea mayor de 16000W*/
select ee.numred_envia, ee.numred_recibe, volumen
from envia_energia ee, red_distribucion rde, estacion ese, red_distribucion rdr, estacion esr
where ee.numred_envia = rde.numred and rde.enombre = ese.enombre
    and ee.numred_recibe = rdr.numred and rdr.enombre = esr.enombre
    and volumen > 16000 and ese.transformadores > esr.transformadores;
    









