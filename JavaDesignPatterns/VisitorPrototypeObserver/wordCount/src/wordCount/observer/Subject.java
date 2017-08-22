package wordCount.observer;

import wordCount.dsForStrings.Node;

/**
 * This is the subject interface.
 */
public interface Subject{
    public void registerObserver(Node n);
    public void notifyObservers();
}
