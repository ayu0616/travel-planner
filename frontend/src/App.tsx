import { Input } from './components/atoms/Input';

function App() {
  return (
    <>
      <h1>旅行プランナー</h1>
      <div className="bg-slate-50 p-4">
        <Input />
        <select className="border"></select>
        <select className="border"></select>
        <input type="checkbox" />
      </div>
    </>
  );
}

export default App;
