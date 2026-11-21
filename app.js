// Frontend demo: expenses stored in an array, rendered in browser.
// The companion C file implements the Linked List operations for the DS coursework.
let expenses = JSON.parse(localStorage.getItem('pocketwise_expenses') || '[]');
const $ = id => document.getElementById(id);
const currency = n => '₹' + Number(n).toLocaleString('en-IN',{minimumFractionDigits:2,maximumFractionDigits:2});
const categories = ['Food','Transport','Shopping','Bills','Health','Education','Entertainment','Other'];
const categoryIcons = {Food:'🍜',Transport:'🚌',Shopping:'🛍️',Bills:'💡',Health:'🩺',Education:'📚',Entertainment:'🎬',Other:'📌'};
function persist(){localStorage.setItem('pocketwise_expenses',JSON.stringify(expenses));}
function escapeHTML(s){return String(s).replace(/[&<>"']/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));}
function render(){
 const total=expenses.reduce((sum,e)=>sum+Number(e.amount),0);
 $('total').textContent=currency(total); $('count').textContent=expenses.length;
 $('average').textContent=currency(expenses.length?total/expenses.length:0);
 $('transactionBadge').textContent=`${expenses.length} record${expenses.length===1?'':'s'}`;
 const q=$('search').value.trim().toLowerCase(), selected=$('filterCategory').value;
 const filtered=expenses.filter(e=>(e.description.toLowerCase().includes(q)||e.category.toLowerCase().includes(q))&&(selected==='All'||e.category===selected));
 $('transactionRows').innerHTML=filtered.map(e=>`<tr><td>${escapeHTML(e.description)}</td><td><span class="category-chip">${categoryIcons[e.category]||'📌'} ${escapeHTML(e.category)}</span></td><td>${escapeHTML(e.date)}</td><td class="amount-cell">${currency(e.amount)}</td><td><button class="delete-btn" data-id="${e.id}" title="Delete expense" aria-label="Delete ${escapeHTML(e.description)}">×</button></td></tr>`).join('');
 $('emptyState').style.display=filtered.length?'none':'block';
 const sums={};expenses.forEach(e=>sums[e.category]=(sums[e.category]||0)+Number(e.amount));
 const sorted=Object.entries(sums).sort((a,b)=>b[1]-a[1]);
 $('categoryList').innerHTML=sorted.length?sorted.map(([cat,val])=>`<div class="category-row"><span class="cat-name">${categoryIcons[cat]||'📌'} ${cat}</span><div class="bar-bg"><div class="bar-fill" style="width:${total?Math.max(2,val/total*100):0}%"></div></div><span class="cat-amount">${currency(val)}</span></div>`).join(''):'<p class="muted empty-cat">Add transactions to see categories.</p>';
 persist();
}
$('expenseForm').addEventListener('submit',e=>{e.preventDefault();const title=$('description').value.trim(),amount=Number($('amount').value),date=$('date').value;if(!title||amount<=0||!date)return;expenses.unshift({id:Date.now(),description:title,amount,category:$('category').value,date});$('description').value='';$('amount').value='';render();});
$('transactionRows').addEventListener('click',e=>{const btn=e.target.closest('.delete-btn');if(!btn)return;expenses=expenses.filter(item=>String(item.id)!==btn.dataset.id);render();});
$('search').addEventListener('input',render);$('filterCategory').addEventListener('change',render);
const today=new Date();$('today').textContent=today.toLocaleDateString(undefined,{weekday:'short',year:'numeric',month:'short',day:'numeric'});$('date').value=today.toISOString().slice(0,10);render();
