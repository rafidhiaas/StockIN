const sheetID = "1gKoT0b7XyQZJhGhHqK-QZleOYYT1BEOiqMwW4qEwzAc";
const sheetName = "list stock"; // ganti sesuai nama sheet kamu
const apiKey = "ISI_API_KEY_KAMU";

const url = `https://sheets.googleapis.com/v4/spreadsheets/${sheetID}/values/${sheetName}?key=${AIzaSyCLVmNiTNZ7UWy-QXvjeVH7lwpQZjKqmZc}`;

fetch(url)
  .then((response) => response.json())
  .then((data) => {
    const rows = data.values;
    const table = document.getElementById("data-table");

    // Hilangkan baris judul
    for (let i = 1; i < rows.length; i++) {
      const row = table.insertRow();
      rows[i].forEach((cell) => {
        const cellElement = row.insertCell();
        cellElement.textContent = cell;
      });
    }
  })
  .catch((error) => {
    console.error("Error fetching data:", error);
  });
