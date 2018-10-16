package mx.ipn.escom.wad.listeners;

import javax.servlet.http.HttpSessionAttributeListener;
import javax.servlet.http.HttpSessionBindingEvent;
import javax.servlet.http.HttpSessionBindingListener;
import javax.servlet.http.HttpSessionEvent;
import javax.servlet.http.HttpSessionListener;

/**
 * Application Lifecycle Listener implementation class EjemploK
 *
 */
public class EjemploK implements HttpSessionListener, HttpSessionBindingListener, HttpSessionAttributeListener {

    /**
     * Default constructor. 
     */
    public EjemploK() {
        System.err.println("--> Instanciando Listener");
    }

	/**
     * @see HttpSessionListener#sessionCreated(HttpSessionEvent)
     */
    public void sessionCreated(HttpSessionEvent e)  { 
         System.err.println("--> Se ha creado la session: "+e.getSession().getId());
    }

	/**
     * @see HttpSessionBindingListener#valueBound(HttpSessionBindingEvent)
     */
    public void valueBound(HttpSessionBindingEvent e)  { 
         System.err.println("--> Se ha agregado un valor: "+e.getName()+" : "+e.getValue());
    }

	/**
     * @see HttpSessionListener#sessionDestroyed(HttpSessionEvent)
     */
    public void sessionDestroyed(HttpSessionEvent e)  { 
    	System.err.println("--> Se ha destruido la session: "+e.getSession().getId());
    }

	/**
     * @see HttpSessionAttributeListener#attributeAdded(HttpSessionBindingEvent)
     */
    public void attributeAdded(HttpSessionBindingEvent e)  { 
    	System.err.println("--> Se ha agregado un atributo: "+e.getName()+" : "+e.getValue());
    }

	/**
     * @see HttpSessionAttributeListener#attributeRemoved(HttpSessionBindingEvent)
     */
    public void attributeRemoved(HttpSessionBindingEvent e)  { 
    	System.err.println("--> Se ha eliminado un atributo: "+e.getName()+" : "+e.getValue());
    }

	/**
     * @see HttpSessionAttributeListener#attributeReplaced(HttpSessionBindingEvent)
     */
    public void attributeReplaced(HttpSessionBindingEvent e)  { 
    	System.err.println("--> Se ha reemplazado un atributo: "+e.getName()+" : "+e.getValue());
    }

	/**
     * @see HttpSessionBindingListener#valueUnbound(HttpSessionBindingEvent)
     */
    public void valueUnbound(HttpSessionBindingEvent e)  { 
    	System.err.println("--> Se ha desvinculado un valor: "+e.getName()+" : "+e.getValue());
    }
	
}
