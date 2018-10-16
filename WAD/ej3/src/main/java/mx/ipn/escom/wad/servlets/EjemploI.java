package mx.ipn.escom.wad.servlets;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import mx.ipn.escom.wad.entidad.Persona;

/**
 * Servlet implementation class EjemploH
 */
public class EjemploI extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public EjemploI() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		out.println("<html>");
		out.println("<head>");
		out.println("</head>");
		out.println("<body>");
		out.println("<h1>Ejemplo I: Include con atributos</h1>");
		RequestDispatcher rd = request.getRequestDispatcher("EjemploI1");
		Integer x = 27;
		String cadena = "Hola Mundo de Atributos";
		Persona persona = new Persona(1, "Hermes Francisco", "Montes", "Casiano", 31);
		request.setAttribute("x", x);
		x=34;
		request.setAttribute("x", x);
		x=null;
		request.setAttribute("x", x);
		request.setAttribute("cadena", cadena);
		request.setAttribute("persona", persona);
		rd.include(request, response);
		out.println("NOTA: estos fueron los parámetros recibidos en la petición");
		out.println("</body>");
		out.println("</html>");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
