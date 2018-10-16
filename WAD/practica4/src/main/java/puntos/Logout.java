package puntos;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class Logout extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
 
    public Logout() {
        super();
       
    }


	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

		doPost(request, response);
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	
		response.setContentType("text/html");  
        PrintWriter out=response.getWriter();      
        HttpSession sesion=request.getSession();  
        sesion.invalidate();  
          
        out.print("Cierre de sesión exitoso");  
          
        out.close();  
	}

}
