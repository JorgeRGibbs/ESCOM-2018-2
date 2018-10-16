package servlets;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.*;

public class Servlet2 extends HttpServlet{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public void doGet(HttpServletRequest request, 
		HttpServletResponse response)throws IOException,ServletException{
			PrintWriter out = response.getWriter();
			response.setContentType("text/html");
			String a = request.getParameter("a");
			String b = request.getParameter("b");
			String c = request.getParameter("c");
			out.println("<html>");
			out.println("<head>");
			out.println("</head>");
			out.println("<body>");
			out.println("<h1>Ejemplo B: extrayendo parámteros</h1>");
			out.println("<p>Los valores de los parámetros son:</p>");
			out.println("<ul>");
			out.println("<li>a="+a+"</li>");
			out.println("<li>b="+b+"</li>");
			out.println("<li>c="+c+"</li>");
			out.println("</ul>");
			out.println("</body>");
			out.println("</html>");
	}

	public void doPost(HttpServletRequest request, 
		HttpServletResponse response)throws IOException,ServletException{
			doGet(request,response);
	}
}