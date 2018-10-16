package mx.ipn.escom.wad.filters;

import java.io.IOException;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


public class FiltroRecursos implements Filter {
	 private ServletContext context;

    public FiltroRecursos() {
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see Filter#destroy()
	 */
	public void destroy() {
		// TODO Auto-generated method stub
		System.out.println("Filtro termina");
		
	}

	/**
	 * @see Filter#doFilter(ServletRequest, ServletResponse, FilterChain)
	 */
	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
		HttpServletRequest peticion = (HttpServletRequest) request;
        HttpServletResponse respuesta = (HttpServletResponse) response;

        HttpSession session = peticion.getSession();

            //RequestDispatcher Dis = peticion.getRequestDispatcher("Practica4/index.html");
            ((HttpServletResponse) response).sendError(503,"Acceso Denegado");
            //Dis.forward(peticion, respuesta);
            chain.doFilter(request, response);
}
	
	public void init(FilterConfig fConfig) throws ServletException {
		this.context = fConfig.getServletContext();
		this.context.log("Filtrando Solicitud");
		//
		System.out.println("Filtro Comienza");
	
	}

}
