package servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Enumeration;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class Ejercicio2
 */
public class ejercicio2 extends HttpServlet {
	private static final long serialVersionUIDx = 1L;

    /**
     * Default constructor. 
     */
    public ejercicio2() {
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see Servlet#init(ServletConfig)
	 */
	public void init(ServletConfig config) throws ServletException {
		// TODO Auto-generated method stub
	}

	/**
	 * @see Servlet#destroy()
	 */
	public void destroy() {
		// TODO Auto-generated method stub
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		Enumeration<String> headers = request.getHeaderNames();
		
		out.println("<html>");
		out.println("<head>");
		out.println("</head>");
		out.println("<body>");
		out.println("<h2> Encabezados </h2>");
		out.println("<br>");
		out.println("<h3> Metodo : " + request.getMethod() + "</h3>");
		out.println("<br>");
		//URI?
		
		while(headers.hasMoreElements())
		{
			String header= (String) headers.nextElement();
			out.println("<h4>" + header+ " :   </h4>");
			out.println(request.getHeader(header));
		}
		out.println("</body>");
		out.println("</html>");
		response.getWriter().append("Servicio  : ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}