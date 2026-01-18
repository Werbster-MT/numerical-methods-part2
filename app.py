import streamlit as st
import subprocess
import pandas as pd
import numpy as np
import os

st.set_page_config(page_title="Sistema Jatos", layout="wide")
st.markdown("""
    <style>
        /* 1. Fonte Geral Grande e Preta (Global) */
        html, body, [class*="css"] {
            font-size: 20px !important;
            color: #000000 !important;
            font-family: 'Segoe UI', sans-serif;
        }

        /* 2. Títulos Gigantes */
        h1 { font-size: 42px !important; font-weight: 800 !important; color: #000000 !important; }
        h2 { font-size: 36px !important; font-weight: 700 !important; color: #000000 !important; }
        h3 { font-size: 28px !important; font-weight: 700 !important; color: #000000 !important; }

        /* 3. Inputs (Caixinhas de números) */
        .stNumberInput input {
            font-size: 20px !important;
            font-weight: bold !important;
            text-align: center !important;
            color: #000000 !important;
        }
        
        /* 4. Títulos de Widgets (Labels) - "Ordem (n)", "Método Numérico" */
        label, .st-emotion-cache-16idsys p {
            font-size: 18px !important;
            color: #000000 !important;
            font-weight: 700 !important;
        }
        
        /* 5. Captions (Textos pequenos explicativos) - "Matriz A (3x3)" */
        [data-testid="stCaptionContainer"] {
            font-size: 18px !important;
            color: #000000 !important;
            font-weight: 600 !important;
        }

        /* 6. SIDEBAR ESPECÍFICO - Força bruta para remover o cinza */
        [data-testid="stSidebar"] {
            font-size: 18px !important;
            color: #000000 !important;
        }
        [data-testid="stSidebar"] h1, [data-testid="stSidebar"] h2, [data-testid="stSidebar"] h3 {
            color: #000000 !important;
        }
        [data-testid="stSidebar"] p, [data-testid="stSidebar"] span, [data-testid="stSidebar"] div {
             color: #000000 !important;
        }
        
        /* 7. Tabelas HTML Personalizadas (Resultados) */
        table.custom-table { width: 100%; border-collapse: collapse; margin-bottom: 20px; }
        table.custom-table th { background-color: #f0f2f6; color: #000000; font-weight: 800; text-align: center !important; padding: 12px; font-size: 22px; border: 1px solid #e0e0e0; }
        table.custom-table td { color: #000000; text-align: center !important; padding: 10px; font-size: 20px; border: 1px solid #e0e0e0; font-weight: 500; }
        table.custom-table tr:nth-child(even) { background-color: #fafafa; }
    </style>
""", unsafe_allow_html=True)

st.title("✈️ Análise Estrutural de Jatos")
st.markdown("Interface gráfica para calcular o deslocamento dos jatos")

def exibir_tabela_html(df):
    html = df.to_html(classes="custom-table", index=False, escape=False)
    st.markdown(html, unsafe_allow_html=True)


with st.sidebar:
    st.header("Configuração")
    
    metodo_escolhido = st.radio(
        "Modo de Operação", 
        ["Fatoração LU", "Fatoração LDP", "Comparativo (LU vs LDP)"]
    )
    
    if metodo_escolhido == "Fatoração LU":
        cod_metodo = "1"
    elif metodo_escolhido == "Fatoração LDP":
        cod_metodo = "2"
    else:
        cod_metodo = "3" 

    st.divider()
    usar_calibracao = st.checkbox("Usar Calibração Padrão (Enunciado)", value=True)
    
    n_input = 3
    df_matriz = None
    df_vetor = None

    if not usar_calibracao:
        st.subheader("Digite a Matriz A")
        n_input = st.number_input("Ordem (n)", 2, 20, 3)
        
        st.caption(f"Matriz A ({n_input}x{n_input})")
        zeros_matriz = np.zeros((n_input, n_input))
        df_matriz = st.data_editor(pd.DataFrame(zeros_matriz, columns=[f"a{i+1}" for i in range(n_input)]), key="m", hide_index=True)

        st.caption(f"Vetor f ({n_input})")
        zeros_vetor = np.zeros((1, n_input))
        df_vetor = st.data_editor(pd.DataFrame(zeros_vetor, columns=[f"f{i+1}" for i in range(n_input)]), key="v", hide_index=True)


if st.button("🚀 Executar Simulação", type="primary"):
    
    input_data = f"{cod_metodo}\n"
    if usar_calibracao:
        input_data += "3\n3 -2 1\n1 -3 4\n9 4 -5\n8 6 11\n"
    else:
        input_data += f"{n_input}\n"
        input_data += " ".join(map(str, df_matriz.values.flatten().tolist())) + "\n"
        input_data += " ".join(map(str, df_vetor.values.flatten().tolist())) + "\n"

    
    executavel = "sistema_jatos.exe" if os.name == 'nt' else "build/./sistema_jatos"
    
    caminho_check = executavel.replace("./", "").replace("build/", "") # Ajuste flexível
    
    try:
        processo = subprocess.run([executavel, "--web"], input=input_data, text=True, capture_output=True)
        saida = processo.stdout
        
        if processo.returncode != 0 and not saida:
             st.error("Erro Numerico. pivô nulo")
             st.stop()

        resultados_simples = []
        resultados_comp = []
        
        for linha in saida.strip().split('\n'):
            if linha.startswith("COMPARE") and ";" in linha:
                partes = linha.split(";") 
                resultados_comp.append({
                    "Parte": partes[1],
                    "LU (cm)": float(partes[2]),
                    "LDP (cm)": float(partes[3]),
                    "Diferença Absoluta": float(partes[4])
                })
            elif ";" in linha and len(linha.split(";")) == 3:
                partes = linha.split(";")
                resultados_simples.append({
                    "Parte": partes[0],
                    "Deslocamento (cm)": float(partes[1]),
                    "Status": partes[2].strip()
                })

        if cod_metodo == "3":
            st.subheader("📊 Quadro Comparativo: LU vs LDP")
            
            if resultados_comp:
                df_comp = pd.DataFrame(resultados_comp)
                
                df_display = df_comp.copy()
                df_display["LU (cm)"] = df_display["LU (cm)"].apply(lambda x: f"{x:.6f}")
                df_display["LDP (cm)"] = df_display["LDP (cm)"].apply(lambda x: f"{x:.6f}")
                df_display["Diferença Absoluta"] = df_display["Diferença Absoluta"].apply(lambda x: f"{x:.2e}")

                exibir_tabela_html(df_display)
                
                erro_total = sum([r["Diferença Absoluta"] for r in resultados_comp])
                st.info(f"💡 **Conclusão Numérica:** A soma total das diferenças entre os métodos é **{erro_total:.2e}**. Isso comprova que o método LDP mantém a precisão do LU.")
                
                st.subheader("Visualização")
                df_chart = pd.melt(df_comp, id_vars=["Parte"], value_vars=["LU (cm)", "LDP (cm)"], var_name="Método", value_name="Valor")
                st.bar_chart(df_chart, x="Parte", y="Valor", color="Método", stack=False)
                
            else:
                st.error("Erro ao ler dados comparativos do C++.")
                st.code(saida)

        else:
            if resultados_simples:
                estavel = all(["CRITICO" not in r["Status"] for r in resultados_simples])
                col1, col2 = st.columns([2,1])
                with col1:
                    if estavel: st.success("✅ **SISTEMA ESTÁVEL** (< 2cm)")
                    else: st.error("💥 **FALHA (JATO EXPLODE)** (> 2cm)")
                    
                    df = pd.DataFrame(resultados_simples)
                    st.bar_chart(df, x="Parte", y="Deslocamento (cm)", color="#00c853" if estavel else "#ff4b4b")
                
                with col2:
                    st.subheader("Dados Detalhados")
                    
                    df_display = df.copy()
                    df_display["Deslocamento (cm)"] = df_display["Deslocamento (cm)"].apply(lambda x: f"{x:.4f}")
                    
                    exibir_tabela_html(df_display)

            else:
                st.error("Erro na leitura.")
                st.code(saida)

    except Exception as e:
        st.error(f"Erro: {e}")