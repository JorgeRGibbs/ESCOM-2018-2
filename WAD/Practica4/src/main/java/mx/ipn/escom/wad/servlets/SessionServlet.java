package mx.ipn.escom.wad.servlets;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import java.io.*;

public class SessionServlet extends HttpServlet{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	protected void doGet(HttpServletRequest request, HttpServletResponse response)  
                      throws ServletException, IOException {  
       doPost(request,response);
    } 
	public void doPost(HttpServletRequest request, 
		HttpServletResponse response)throws IOException,ServletException{
			PrintWriter out = response.getWriter();
			response.setContentType("text/html");
			
			HttpSession session= request.getSession(); //
			if(session!=null ) {
				String usuario = (String)session.getAttribute("usuario");
				if(usuario!=null) {	
					out.println("Bienvenido ,"+usuario+"!");
				}else
				{
					out.println("No existe una sesión activa, ingrese.");
				//
					request.getRequestDispatcher("/login.html")
						.include(request, response);
				}
			}
			out.close();
	}
}