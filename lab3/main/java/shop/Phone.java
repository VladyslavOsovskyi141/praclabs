package main.java.shop;
public class Phone implements Product {
    @Override
    public String getName() {
        return "Phone";
    }

    @Override
    public double getPrice() {
        return 12000;
    }
}