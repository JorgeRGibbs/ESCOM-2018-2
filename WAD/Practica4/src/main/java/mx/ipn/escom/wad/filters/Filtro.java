package mx.ipn.escom.wad.filters;

import java.io.IOException;
import java.time.LocalDateTime;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;

/**
 * Servlet Filter implementation class Filtro
 */
public class Filtro implements Filter {
	private ServletContext context;
	/**
	 * Default constructor.
	 */
	public Filtro() {
		super();
	}

	/**
	 * @see Filter#destroy()
	 */
	public void destroy() {
		System.out.println("Finalizando Filtro");
	}

	/**
	 * @see Filter#doFilter(ServletRequest, ServletResponse, FilterChain)
	 */
	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
			throws IOException, ServletException {
		
		//System.out.println("Filter: ");
		System.out.println("Filter: Filtrando petición...");
		//Inicio edit
		System.out.println("Fecha y Hora:"+LocalDateTime.now());
		HttpServletRequest req = (HttpServletRequest) request;
		//String method = request.getMethod();
		System.out.println("Método:"+req.getMethod());
		System.out.println("Recurso:"+this.getClass().getResource("/index.html"));
		System.out.println("IP_Addr:"+request.getRemoteAddr());
		//Fin edit
		chain.doFilter(request, response);
		//System.out.println("Filter: Después");
	}
	
	

	/**
	 * @see Filter#init(FilterConfig)
	 */
	public void init(FilterConfig fConfig) throws ServletException {
		System.out.println("Inicializando Filtro");
	}

}
