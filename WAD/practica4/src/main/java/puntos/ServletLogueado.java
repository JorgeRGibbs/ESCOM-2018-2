package puntos;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


public class ServletLogueado extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    
    public ServletLogueado() {
        super();
        
    }

	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doPost(request,response);
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		//response.setContentType("/text/html");
		PrintWriter out = response.getWriter();
		HttpSession sesion=request.getSession(false);
		if(sesion!=null) {
		String user=(String)sesion.getAttribute("usuario");
		response.setContentType("text/html");
		out.print("<title> Bienvenido!</title>");
		out.print("<h3>Hola "+ user+"</h3>");
		
			if(user == null) { response.sendRedirect("login.html");}
		}
		
	}
		
	}


