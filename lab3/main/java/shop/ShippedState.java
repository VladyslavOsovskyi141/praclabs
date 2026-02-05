package main.java.shop;

public class ShippedState implements OrderState {
    @Override
    public void next(OrderContext order) {
        order.setState(new DeliveredState());
    }

    @Override
    public String getStatus() {
        return "Shipped";
    }
}
