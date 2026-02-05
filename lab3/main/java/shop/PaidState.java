package main.java.shop;

public class PaidState implements OrderState {
    @Override
    public void next(OrderContext order) {
        order.setState(new ShippedState());
    }

    @Override
    public String getStatus() {
        return "Paid";
    }
}
