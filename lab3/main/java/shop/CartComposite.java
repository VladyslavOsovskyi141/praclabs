package main.java.shop;

import java.util.ArrayList;
import java.util.List;

public class CartComposite implements CartComponent {
    private List<CartComponent> items = new ArrayList<>();

    public void add(CartComponent component) {
        items.add(component);
    }

    @Override
    public double getPrice() {
        double sum = 0;
        for (CartComponent c : items) {
            sum += c.getPrice();
        }
        return sum;
    }

    @Override
    public void show() {
        for (CartComponent c : items) {
            c.show();
        }
    }
}
