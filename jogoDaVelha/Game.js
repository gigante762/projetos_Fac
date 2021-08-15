class Game
{
    constructor(tab)
    {
        this.tab = tab;
        this.vezX = true; // vez do jogador X
        this.addEventsToSlots();
        this.hasWinner = false;
    }

    printTable(){
        this.tab.printTable();
    }

    addEventsToSlots()
    {
        let slots = Array.from(document.querySelectorAll('.slot'))
        slots.forEach((slot)=>{
            slot.addEventListener('click',(el)=>{
                let x = slot.getAttribute('x');
                let y = slot.getAttribute('y');
                //console.log('Jogar: ', x, y)
                this.play(x,y);
            })
        })
        let vez = this.vezX ? "X" : "O";
        let vezele = document.getElementById('vezel');
        vezele.innerText = vez;
        vezele.className = vez;
    }

    play(x,y)
    {
        if (this.hasWinner)
        {
            //console.log("Jogo finalizado por conta do vencedor");
            return;
        }

        if (this.tab.data[y][x] == ' ')
        {
            let vez = this.vezX ? "X" : "O";
            this.tab.data[y][x] = vez;

           
            this.tab.updateTab();

            this.hasWinner = this.checkWinner()
                

            this.vezX = !this.vezX;
            vez = this.vezX ? "X" : "O";
            let vezele = document.getElementById('vezel');
            vezele.innerText = vez;
            vezele.className = vez;


        }
    }

    checkWinner()
    {
        let vez = (this.vezX) ? "X" : "O"; // char
        let matrixBoolBasedVez = [[],[],[]]// this.tab.data;

        for (let y = 0; y < this.tab.data.length; y++) {
            for (let x = 0; x < this.tab.data[y].length; x++) {
               matrixBoolBasedVez[y][x] = (this.tab.data[y][x] == vez)
            }
        }

        /* Fiquei feliz com o algoritmo que se me ocurrio */
        for (let y = 0; y < this.tab.data.length; y++) {
            let wonLinha = true;
            let wonColuna = true;
            let wonDiagonalEtD = true;
            let wonDiagonalDtE = true;
            for (let x = 0; x < this.tab.data[y].length; x++) {
                wonLinha = wonLinha && matrixBoolBasedVez[y][x];
                wonColuna = wonColuna && matrixBoolBasedVez[x][y];
                wonDiagonalEtD = wonDiagonalEtD && matrixBoolBasedVez[x][x];
            }
            // y,x => 0,2 1,1 2,0
            wonDiagonalDtE = wonDiagonalDtE &&
                matrixBoolBasedVez[0][2] &&
                matrixBoolBasedVez[1][1] &&
                matrixBoolBasedVez[2][0];
                

            if (wonLinha)
            {
                //console.log("Ganhou na linha ",y);
                this.tab.setWinner('l',y);
                return true;
            }
            if (wonColuna)
            {
                this.tab.setWinner('c',y);
                //console.log("Ganhou na coluna ",y);
                return true;
            }
            if (wonDiagonalEtD)
            {
                this.tab.setWinner('d',1);
                //console.log("Ganhou na coluna Diagonal Esquerda pra direita");
                return true;
            }
            if (wonDiagonalDtE)
            {
                this.tab.setWinner('d',2);
                //console.log("Ganhou na coluna Diagonal Direita pra esquerda");
                return true;
            }
        }

        

        //console.table(matrixBoolBasedVez);
        return false;

        
    }


    
    
}