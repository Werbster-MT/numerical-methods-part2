import os


config_content = """
[theme]
base="light"
primaryColor="#ff4b4b"
backgroundColor="#ffffff"
secondaryBackgroundColor="#f0f2f6"
textColor="#000000"
font="sans serif"
"""


if not os.path.exists(".streamlit"):
    os.makedirs(".streamlit")
    print("Pasta .streamlit criada.")


with open(".streamlit/config.toml", "w") as f:
    f.write(config_content)

print("✅ SUCESSO! Arquivo de configuração criado.")
print("Agora reinicie seu app (Ctrl+C e depois 'streamlit run app.py')")