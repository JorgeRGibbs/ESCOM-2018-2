package puntos;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


public class ServletPublico extends HttpServlet {
	private static final long serialVersionUID = 1L;
       

    public ServletPublico() {
        super();
    }

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		PrintWriter out= response.getWriter();
		response.setContentType("text/html");
		out.println("<html><body>");
		out.println("<p>Alejandro Muñoz Moreno. Figura de la Lucha Libre, más que la de un héroe, aparece como la de un icono popular. Blue Demon o El demonio azul era un joven regiomontano que se inició en la lucha bajo la protección del maestro Rolando Vera. Filmó varias películas y murió a causa de un infarto.</p>");
		out.println("</body></html>");
	}


	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		doGet(request, response);
	}

}
