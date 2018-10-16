package mx.ipn.escom.wad.servlets;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import java.io.*;
//necaxa
//aguinaga
public class Servlet1 extends HttpServlet{
	private static final long serialVersionUID = 1L;
	private final String vuser ="necaxa";
	private final String vpass ="aguinaga";
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doPost(request, response);
	}
	
	public void doPost(HttpServletRequest request, 
		HttpServletResponse response)throws IOException,ServletException{
			PrintWriter out = response.getWriter();
			
			String usuario = request.getParameter("usuario");
			String password = request.getParameter("password");
			
			if(vuser.equals(usuario) && vpass.equals(password))
			{
				HttpSession session = request.getSession();
				/**/
				//
				session.setAttribute("usuario",usuario);
				session.setAttribute("password",password);
				response.sendRedirect("SessionServlet");
			}else {
				RequestDispatcher Dis = 
				getServletContext().getRequestDispatcher("/login.html");
				out.println("<a>Error intentelo otra vez</a>");
				//out.println("<a>Das war ein Fehler!, versuchen sie noch einmal.</a>");
				Dis.include(request,response);
			}
	}
}