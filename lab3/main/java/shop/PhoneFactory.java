package main.java.shop;
public class PhoneFactory extends ProductFactory {
    @Override
    public Product createProduct() {
        return new Phone();
    }
}