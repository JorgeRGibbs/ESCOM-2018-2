package puntos;

import java.io.IOException;
import java.util.Date;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletResponse;


public class FilterIP implements Filter {
	private ServletContext context;
    	public FilterIP() {
    	super();
    }

	public void destroy() {
	}
	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
		String ip= request.getRemoteAddr();
		Date date= new Date();
	
		System.out.println("Filter:"+ip+ " " + date);
		
		
		
		chain.doFilter(request, response);
	//	httpResponse.sendRedirect("/practica3");
		
	}

	public void init(FilterConfig fConfig) throws ServletException {
		System.out.println("-->Filtro publico monitoreando");
	
	}

}
