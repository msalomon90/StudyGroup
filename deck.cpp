#include "deck.h"
#include "ui_deck.h"

#include <QDebug>

Deck::Deck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deck)
{
    ui->setupUi(this);
}

Deck::~Deck()
{
    delete ui;
}

// When a new card needs to be properly inserted/edited
void Deck::init_card(int index, QString text, bool front_side)
{
    // Is this a new card?
    if(edit_card(index, text, front_side)){
        return;
    }
    else { // New card!
        qDebug() << "Deck size: "<< deck.size() <<endl;
        qDebug() << "Adding new card at" << index;
        while(deck.size()-1 < index) { // If the index we get is out of range, put nullptrs in until we get to where we want
            deck.append(nullptr);
        }

        Flashcard* new_card;
        if(front_side) {
            new_card = new Flashcard(text, "", index);
        }
        else {
            new_card = new Flashcard("", text, index);
        }

        connect(new_card, SIGNAL(check_set_card(Flashcard*,QString&,int&,int)), this, SLOT(check_set_card(Flashcard*,QString&,int&,int)));
        deck[++index] = new_card; // The above loop guarantees we are in the proper spot to append at the right index
                                  // even if the index was too high at first
        if(deck.size() > 1)
        {
            ui->prev_btn->show(); // Show the prev/next buttons
            ui->next_btn->show();
        } else {
            current_index = index; // If first card AND back is defined, set that in the stacked widget
            ui->stackedWidget_card_edit->addWidget(new_card);
            ui->stackedWidget_card_edit->setCurrentWidget(new_card);
        }
    }
}

QString Deck::get_card_text(){
    //return flashcard->get_card_text();
}

void Deck::deleteCard(int index){
    Flashcard* temp = deck[index];
    deck[index] =deck[deck.size()-1];
    deck[deck.size()-1] = temp;
    deck.pop_back();
}

void Deck::add_card()
{
    int new_index = -1;
    emit set_card("", new_index, 0); // Emit new card signal first thing to receive index
    init_card(0, "", true); // Make new card

    ui->stackedWidget_card_edit->removeWidget(deck.at(0));
    current_index = 0;
    ui->stackedWidget_card_edit->addWidget(deck.at(0));        // Hard coded index for testing card
    ui->stackedWidget_card_edit->setCurrentWidget(deck.at(0)); // ^
}

// to be called only from here
// When we want no chance of making a new card
// returns true if editing existing card, false if new card
bool Deck::edit_card(int index, QString text, bool front_side)
{
    // Is this a new card?
    if((index < deck.size()) && (deck.at(index) != nullptr)) { // Editing existing card
        if(front_side)
        {
            deck.at(index)->setFront(text);
        }
        else {
            deck.at(index)->setBack(text);
        }
        return true;
    }
    return false;
}

int Deck::getDeckSize()
{
    return deck.size();
}

void Deck::check_set_card(Flashcard* card, QString& text, int& index, int side)
{
    if(side == 0) { // Front
        emit set_card(text, index, side); // The index returned is index
        edit_card(index, text, true); // Edit card with proper index
    }
    else { // Back
        emit set_card(text, index, side);
        edit_card(index, text, false); // Edit
        if(ui->stackedWidget_card_edit->currentIndex() > 0) {
            ui->stackedWidget_card_edit->removeWidget(card); // Remove the card (done editing)
        }
    }
}

void Deck::on_prev_btn_clicked()
{
    ui->stackedWidget_card_edit->removeWidget(deck.at(current_index)); // Remove the widget currently displayed
    do {
        if(quiz) {
            current_index = rand() % deck.size();
        } else {
            current_index = (current_index - 1) < 0 ? deck.size() - 1 : current_index - 1; // Update index
            // If current index - 1 is negative, loop back to top. Otherwise, current_index - 1.
        }
    } while(deck.at(current_index) == nullptr); // Keep updating until we get to one that isnt a nullptr

    ui->stackedWidget_card_edit->addWidget(deck.at(current_index)); // Add the widget at the new index
    ui->stackedWidget_card_edit->setCurrentWidget(deck.at(current_index)); // Make sure its the one being displayed

}

void Deck::on_next_btn_clicked()
{
    ui->stackedWidget_card_edit->removeWidget(deck.at(current_index)); // Remove the widget currently displayed
    do {
        if(quiz) {
            current_index = rand() % deck.size();
        } else {
            current_index = (current_index + 1) % deck.size(); // Update index, mod so it loops back to beginning if too far
        }
    } while(deck.at(current_index) == nullptr); // Keep updating until we get to one that isnt a nullptr

    ui->stackedWidget_card_edit->addWidget(deck.at(current_index)); // Add the widget at the new index
    ui->stackedWidget_card_edit->setCurrentWidget(deck.at(current_index)); // Make sure its the one being displayed
}

void Deck::set_quiz(bool is_set)
{
    quiz = is_set;
    if(deck.size() > 0) { // Make sure that the deck even has any cards...
        ui->stackedWidget_card_edit->removeWidget(deck.at(current_index));  // remove current displayed widget
        if(quiz) {
            current_index = rand() % deck.size();
            ui->stackedWidget_card_edit->addWidget(deck.at(current_index)); // Put random
        }
        else {
            current_index = 0;
            ui->stackedWidget_card_edit->addWidget(deck.at(current_index)); // Put first card
        }
    }
}
