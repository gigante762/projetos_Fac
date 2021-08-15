class Tab 
{
    constructor(div)
    {
        this.el = document.getElementById(div);
        this.data =  [
            [' ', ' ', ' '],
            [' ', ' ', ' '],
            [' ', ' ', ' '],
        ];
       
    }

    printTable()
    {
        // delete table
        this.el.innerHTML = '';

        this.data.map((row,y)=>{
            let rowel = document.createElement('div');
            rowel.classList.add('row');
            row.map((col,x)=>{
                let colel  = document.createElement('div');
                colel.classList.add('slot');
                if (col == 'X')
                    colel.classList.add('X');
                else if (col == 'O')
                    colel.classList.add('O');
                colel.innerText = col;
                colel.setAttribute('x',x) 
                colel.setAttribute('y',y) 
                rowel.appendChild(colel);
            })
            this.el.appendChild(rowel);
        })
        
    }

    updateTab(){
        let slots = Array.from(document.querySelectorAll('.slot'));
        let vezele = document.getElementById('vezel')
        vezele.className = ''


        slots.map((slotel)=>{
            let x = slotel.getAttribute('x');
            let y = slotel.getAttribute('y');
            slotel.className = 'slot';
            let value = this.data[y][x];
            slotel.innerText = value;
    
            if (value == 'X')
                slotel.classList.add('X');
            else if (value == 'O')
                slotel.classList.add('O');
        })
    }

    /* l, c, d = linha, coluna e diagonais */
    setWinner(lcd, pos)
    {
        let slots = Array.from(document.querySelectorAll('.slot'));
        let a = [];
        a.push(slots.splice(0,3));
        a.push(slots.splice(0,3));
        a.push(slots.splice(0,3));

        if (lcd == 'l')
        {
            for (let i = 0; i < 3; i++) {
                a[pos][i].classList.add('win');   
            }
        }
        else if (lcd == 'c')
        {
            for (let i = 0; i < 3; i++) {
                a[i][pos].classList.add('win');          
            }
        }
        else if (lcd == 'd')
        {
            if (pos == 1)
            {
                for (let i = 0; i < 3; i++) {
                    a[i][i].classList.add('win');   
                }
            }
            else
            {
                for (let i = 0; i < 3; i++) {
                    a[0][2].classList.add('win');   
                    a[1][1].classList.add('win');   
                    a[2][0].classList.add('win');   
                }
            }
           
        }
        
        return true;


        

    }

}