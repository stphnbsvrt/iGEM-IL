import java.lang.reflect.*;
import java.util.Arrays;

public class ControlHandler {
    private Class controlClass;
    private Object controller;
    private Method[] methods;
    private static final String[] REQ_METHODS = {"requestCommand", "update"};

    public ControlHandler(String className) throws Exception {
	controlClass = Class.forName(className);
	/*
	try {
	    controlClass = Class.forName(className);
	} catch (ClassNotFoundException e) {
	    System.err.println(e.toString);
	}
	*/
	Method[] allMethods = controlClass.getMethods();
	methods = new Method[REQ_METHODS.length];

	for(int i = 0; i < REQ_METHODS.length; i++) {
	    for(int j = 0; j < allMethods.length; j++) {
		if(allMethods[j].getName() == REQ_METHODS[i]) {
		    methods[j] = allMethods[i];
		    break;
		}
		if(j == allMethods.length - 1) {
		    throw new IllegalArgumentException("Class missing required methods.");
		}
	    }
	}
	
	controller = controlClass.newInstance();
	/*try {
	    controller = controlClass.newInstance();
	} catch (InstantiationException | IllegalAccessException e) {
	    System.err.println(e.toString());
	}*/
    }

    public void update(Object[] params) {
	String methodName = "update";
	int i = Arrays.binarySearch(REQ_METHODS, methodName);
	try {
	    methods[i].invoke(controller, params); 
	} catch (IllegalAccessException | InvocationTargetException e) {
	    System.err.println(e.toString());
	}
    }

    public String requestCommand() {
	String methodName = "requestCommand";
	int i = Arrays.binarySearch(REQ_METHODS, methodName);
	String command;
	try {
	    command = (String) methods[i].invoke(controller);
	    return command;
	} catch (IllegalAccessException | InvocationTargetException e) {
	    System.err.println(e.toString());
	}
	
	return null;
    }

    public static void main(String[] args) {
	try {
	    ControlHandler a = new ControlHandler(args[0]);
	} catch (Exception e) {
	    System.out.println(e.toString());
	}
    }

}