public abstract class ArduinoModule {
    
    private int eepromLocation;
    private String[] pins;

    public ArduinoModule(int eepromLocation) {
	this.eepromLocation = eepromLocation;
    }

    public abstract void update(Object[] params);
    public abstract String requestCommand();

}