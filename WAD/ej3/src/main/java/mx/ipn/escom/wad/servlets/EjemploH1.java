package mx.ipn.escom.wad.servlets;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import mx.ipn.escom.wad.entidad.Persona;

/**
 * Servlet implementation class EjemploH1
 */
public class EjemploH1 extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public EjemploH1() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		Integer x = (Integer) request.getAttribute("x");
		Integer y = (Integer) request.getAttribute("y");
		String cadena = (String) request.getAttribute("cadena");
		Persona persona = (Persona) request.getAttribute("persona");
		out.println("<ul>");
		out.println("<li>" + x + "</li>");
		out.println("<li>" + y + "</li>");
		out.println("<li>" + cadena + "</li>");
		out.println("<li>Persona:");
		out.println("<ul>");
		out.println("<li>" + persona.getId() + "</li>");
		out.println("<li>" + persona.getNombre() + "</li>");
		out.println("<li>" + persona.getPrimerApellido() + "</li>");
		out.println("<li>" + persona.getSegundoApellido() + "</li>");
		out.println("<li>" + persona.getEdad() + "</li>");
		out.println("</ul>");
		out.println("</li>");
		out.println("</ul>");
		out.println("</body>");
		out.println("</html>");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
