package puntos;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


public class ServletLogin extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private final String us="necaxa";
	private final String p="aguinagua";

	public ServletLogin() {
    		
        super();
       
    }
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doPost(request, response);
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		PrintWriter out= response.getWriter();
		
		String usuario=request.getParameter("usuario");
		String password=request.getParameter("password");
		System.out.println(usuario+" "+password);

		if(us.equals(usuario)&&p.equals(password)){
			HttpSession sesion=request.getSession();
			sesion.setAttribute("usuario",usuario);
			sesion.setAttribute("password", password);
			response.sendRedirect("/practica4/Sesion");
		}
		else {
			RequestDispatcher rd=getServletContext().getRequestDispatcher("/login.html"); 
			out.println("<font color=red>Nombre o contraseña incorrectos</font>");
	       rd.include(request, response);  


		}
	}

}
