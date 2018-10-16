package mx.ipn.escom.wad.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;
import java.util.Enumeration;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import mx.ipn.escom.wad.entidad.Persona;

/**
 * Servlet implementation class EjemploJ
 */
public class EjemploJ extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public EjemploJ() {
        super();
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
		out.println("<h1>Ejemplo J:HttpSessions</h1>");
		HttpSession session = request.getSession(false);
		if(session == null) {
			session = request.getSession();
			out.println("<h3>La sesión no existía, se creó una el: "+new Date(session.getCreationTime())+"</h3>");
		} else {
			out.println("<h3>La sesión ya existía, se creó una el: "+new Date(session.getCreationTime())+"</h3>");
		}
		out.println("<ul>");
		out.println("<li>isNew? = "+session.isNew()+"</li>");
		out.println("<li>ID = "+session.getId()+"</li>");
		out.println("<li>LastAccessedTime = "+new Date(session.getLastAccessedTime())+"</li>");
		out.println("<li>MaxInactiveInterval = "+session.getMaxInactiveInterval()+"</li>");
		Enumeration<String> attributeNames = session.getAttributeNames();
		out.println("<li>Attributes: </li>");
		out.println("<ul>");
		while(attributeNames.hasMoreElements()) {
			String attributeName = attributeNames.nextElement();
			out.println("<li>"+attributeName+" = "+session.getAttribute(attributeName)+"</li>");
			session.removeAttribute(attributeName);
		}
		out.println("</ul>");
		out.println("</ul>");
		out.println("</body>");
		out.println("</html>");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		Integer id = Integer.parseInt(request.getParameter("id"));
		String nombre = request.getParameter("nombre");
		String primerApellido = request.getParameter("primerApellido");
		String segundoApellido = request.getParameter("segundoApellido");
		Integer edad = Integer.parseInt(request.getParameter("edad"));
		Persona p = new Persona(id, nombre, primerApellido, segundoApellido, edad);
		HttpSession session = request.getSession();
		session.setAttribute("persona", p);
		session.putValue("xxx", "x");
		response.sendRedirect("EjemploJ");
	}

}
