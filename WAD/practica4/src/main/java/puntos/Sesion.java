package puntos;
import java.io.IOException;  
import java.io.PrintWriter;  
import javax.servlet.ServletException;  
import javax.servlet.http.HttpServlet;  
import javax.servlet.http.HttpServletRequest;  
import javax.servlet.http.HttpServletResponse;  
import javax.servlet.http.HttpSession;  
public class Sesion extends HttpServlet {  
   
	private static final long serialVersionUID = 1L;
	protected void doGet(HttpServletRequest request, HttpServletResponse response)  
                      throws ServletException, IOException {  
       doPost(request,response);
    } 
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    	 response.setContentType("text/html");  
         PrintWriter out=response.getWriter();  
           
         HttpSession session=request.getSession(false);  
         if(session!=null){  
         String name=(String)session.getAttribute("usuario");  
           
         out.print("Hola, "+name+" sesión abierta");  
         }  
         else{  
             out.print("Por favor ingresa al sitio primero");  
             request.getRequestDispatcher("login.html").include(request, response);  
         }  
         out.close();  
    }
}  
