package mx.ipn.escom.wad.servlets;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class EjemploE
 */
public class EjemploE extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public EjemploE() {
		super();
	}

	/**
	 * @see Servlet#init(ServletConfig)
	 */
	public void init(ServletConfig config) throws ServletException {
		System.out.println("Inicializando servlet: EjemploE");
		String a = config.getInitParameter("a");
		String b = config.getInitParameter("b");
		String c = config.getInitParameter("c");
		System.out.println("---> Parámetros de inicialización: " + a + " - " + b + " - " + c);
	}

	/**
	 * @see Servlet#destroy()
	 */
	public void destroy() {
		System.out.println("Finalizando servlet: EjemploE");
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		out.println("<html>");
		out.println("<head>");
		out.println("</head>");
		out.println("<body>");
		out.println("<h1>Ejemplo E: Ciclo de vida de un servlet</h1>");
		out.println("</body>");
		out.println("</html>");
	}
}
