package main.java.shop;

public class DeliveredState implements OrderState {
    @Override
    public void next(OrderContext order) {
        System.out.println("Order already delivered.");
    }

    @Override
    public String getStatus() {
        return "Delivered";
    }
}
