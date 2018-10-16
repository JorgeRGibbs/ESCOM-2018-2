package puntos;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


public class ServletPrivado extends HttpServlet {
	private static final long serialVersionUID = 1L;
       

    public ServletPrivado() {
        super();
    }

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		PrintWriter out= response.getWriter();
		response.setContentType("text/html");
		out.println("<html><body>");
		out.println("<p> ¿Fue todo un sueño? Algunos dicen que a Oliver le cortaron las piernas por el accidente que sufrió cuando era niño y que toda la serie fue producto de su mente.<br>Sin embargo, el verde capitulo final es abierto. Japón va a iniciar el Mundial ante el Brasil de Roberto Sedinho con sus estrellas Atom, Steve Hyuga y Benji Price El deseo de todos es que continúe esta serie que nos marcó de niños.<br> Hay muchos rumores sobre su posible vuelta. A esperar... </p>");
		out.println("</body></html>");
	}


	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
