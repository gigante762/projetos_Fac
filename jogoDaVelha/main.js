// main

let tab = new Tab('table')
let game = new Game(tab)
game.printTable();
game.addEventsToSlots();


document.getElementById('resetBtn').addEventListener('click',()=>{

    tab = new Tab('table');
    game = new Game(tab)
    game.printTable();
    game.addEventsToSlots();

})

