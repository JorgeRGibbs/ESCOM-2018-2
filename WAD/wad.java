//21 de Septiembre de 2018
//WAD

//Bloquear x tiempo
//si el ingreso falla n veces en un intervalo de tiiempo 

//mapeo de ORM
//Solo se mapearon primitivos
//Se debe mapear en una clase todos los not null en una tabla

@Entity
@Table(name  "usuario"

//se le debe indicar la primary key a ORM como se hace en la clase con el entero id, si la llave es simple	)

public Class Usuario
{
	@Id
	@Column (name ="id_usuario");
	private Integer id;
	@Column(name ="id_rol");
	private String nombre;
}