' ----------------------------------------------------------------------------------------------
'   AUTEUR: Jan Huijghebaert
'   BESCHRIJVING: Grafical User Interface voor het aansturen van de StingRay Robot.
' ----------------------------------------------------------------------------------------------

' Imports
Imports System.IO.Ports

' Venster 1
Public Class Venster1

    ' Variabelen
    Dim state As Integer = 0
    Dim mijn_poorten As Array
    Dim baudrate_lijst As Array = {"300", "600", "1200", "2400", "4800", "9600", "14400", "19200", "28800", "38400", "57600", "115200"}
    Dim baudrate As Integer
    Delegate Sub SetTextCallBack(ByVal [tekst] As String)

    ' Opstarten van de GUI
    Private Sub Venster1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        mijn_poorten = IO.Ports.SerialPort.GetPortNames
        cb_COMpoort.Items.AddRange(mijn_poorten)
        cb_Baudrate.Items.AddRange(baudrate_lijst)
        b_sluit.Enabled = False
        Disable_Controls()
        Reset_Controls()
        b_zend.Enabled = False
        b_annuleren.Enabled = False
    End Sub

    ' Button refresh
    Private Sub b_refresh_Click(sender As Object, e As EventArgs) Handles b_refresh.Click
        mijn_poorten = IO.Ports.SerialPort.GetPortNames
        cb_COMpoort.Items.AddRange(mijn_poorten)
    End Sub

    ' Button open terminal
    Private Sub b_open_Click(sender As Object, e As EventArgs) Handles b_open.Click
        If (cb_COMpoort.Text.Equals("") Or cb_Baudrate.Text.Equals("")) Then
            rtb_Terminal.ForeColor = Color.Red
            rtb_Terminal.Text = "------ INSTELLINGEN ONVOLLEDIG ------"
            If (cb_COMpoort.Text.Equals("")) Then
                rtb_Terminal.Text = rtb_Terminal.Text + vbCr + vbCr + "Kies een COM-poort"
            End If
            If (cb_Baudrate.Text.Equals("")) Then
                rtb_Terminal.Text = rtb_Terminal.Text + vbCr + "Kies een baudrate"
            End If
            rtb_Terminal.Text = rtb_Terminal.Text + vbCr + "---------------------------------------------------------"
        Else
            SerialPort1.PortName = cb_COMpoort.Text
            SerialPort1.BaudRate = cb_Baudrate.Text
            SerialPort1.Open()

            cb_COMpoort.Enabled = False
            cb_Baudrate.Enabled = False

            rtb_Terminal.ForeColor = Color.Aqua
            rtb_Terminal.Text = "Terminal op " + cb_COMpoort.Text + " open" + vbCr

            b_open.Enabled = False
            b_refresh.Enabled = False
            b_sluit.Enabled = True
            Enable_Controls()
        End If
    End Sub

    ' Button sluit terminal
    Private Sub b_sluit_Click(sender As Object, e As EventArgs) Handles b_sluit.Click
        SerialPort1.Close()

        cb_COMpoort.Enabled = True
        cb_Baudrate.Enabled = True

        rtb_Terminal.Text = rtb_Terminal.Text + "Terminal op " + cb_COMpoort.Text + " gesloten" + vbCr

        b_open.Enabled = True
        b_refresh.Enabled = True
        b_sluit.Enabled = False
        Disable_Controls()
        Reset_Controls()
        b_zend.Enabled = False
        b_annuleren.Enabled = False
    End Sub

    ' Button over
    Private Sub b_over_Click(sender As Object, e As EventArgs) Handles b_over.Click
        Venster2.Show()
    End Sub

    ' Data ontvangen van Arduino
    Private Sub SerialPort1_DataReceived(sender As Object, e As SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        ReceivedText(SerialPort1.ReadExisting())
    End Sub

    ' Binnengekomen data lezen en afdrukken in terminal
    Private Sub ReceivedText(ByVal [tekst] As String)
        If Me.rtb_Terminal.InvokeRequired Then
            Dim x As New SetTextCallBack(AddressOf ReceivedText)
            Me.Invoke(x, New Object() {(tekst)})
        Else
            rtb_Terminal.Text = rtb_Terminal.Text + [tekst]
        End If
    End Sub

    ' Button ping links
    Private Sub b_pingl_Click(sender As Object, e As EventArgs) Handles b_pingl.Click
        rtb_Terminal.Text = rtb_Terminal.Text + "PC: PING links afstand?" + vbCr
        ' ZENDEN
        rtb_Terminal.Text = rtb_Terminal.Text + "NC" + vbCr
    End Sub

    ' Button ping midden
    Private Sub b_pingm_Click(sender As Object, e As EventArgs) Handles b_pingm.Click
        rtb_Terminal.Text = rtb_Terminal.Text + "PC: PING midden afstand?" + vbCr
        ' ZENDEN
        rtb_Terminal.Text = rtb_Terminal.Text + "NC" + vbCr
    End Sub

    ' Button ping rechts
    Private Sub b_pingr_Click(sender As Object, e As EventArgs) Handles b_pingr.Click
        rtb_Terminal.Text = rtb_Terminal.Text + "PC: PING rechts afstand?" + vbCr
        ' ZENDEN
        rtb_Terminal.Text = rtb_Terminal.Text + "NC" + vbCr
    End Sub

    ' Button rechtdoor
    Private Sub b_forward_Click(sender As Object, e As EventArgs) Handles b_forward.Click
        Reset_Controls()
        b_forward.BackColor = Color.GreenYellow
        'Disable_Controls()

        tb_afstand.Enabled = True
        tb_afstand.BackColor = Color.GreenYellow
        tb_snelheid.Enabled = True
        tb_snelheid.BackColor = Color.GreenYellow

        b_zend.Enabled = True
        b_annuleren.Enabled = True

        SerialPort1.Write("z")
        rtb_Terminal.Text = rtb_Terminal.Text + "PC: stuur 'z'" + vbCr
    End Sub

    ' Button achteruit
    Private Sub b_backward_Click(sender As Object, e As EventArgs) Handles b_backward.Click
        Reset_Controls()
        b_backward.BackColor = Color.GreenYellow
        'Disable_Controls()

        tb_afstand.Enabled = True
        tb_afstand.BackColor = Color.GreenYellow
        tb_snelheid.Enabled = True
        tb_snelheid.BackColor = Color.GreenYellow

        b_zend.Enabled = True
        b_annuleren.Enabled = True

        SerialPort1.Write("s")
        rtb_Terminal.Text = rtb_Terminal.Text + "PC: stuur 's'" + vbCr
    End Sub

    ' Button links draaien
    Private Sub b_left_Click(sender As Object, e As EventArgs) Handles b_left.Click
        Reset_Controls()
        b_left.BackColor = Color.GreenYellow
        'Disable_Controls()

        tb_snelheid.Enabled = True
        tb_snelheid.BackColor = Color.GreenYellow
        tb_draaihoek.Enabled = True
        tb_draaihoek.BackColor = Color.GreenYellow
        tb_radius.Enabled = True
        tb_radius.BackColor = Color.GreenYellow

        b_zend.Enabled = True
        b_annuleren.Enabled = True

        SerialPort1.Write("d")
        rtb_Terminal.Text = rtb_Terminal.Text + "PC: stuur 'q'" + vbCr
    End Sub

    ' Button rechts draaien
    Private Sub b_right_Click(sender As Object, e As EventArgs) Handles b_right.Click
        Reset_Controls()
        b_right.BackColor = Color.GreenYellow
        'Disable_Controls()

        tb_snelheid.Enabled = True
        tb_snelheid.BackColor = Color.GreenYellow
        tb_draaihoek.Enabled = True
        tb_draaihoek.BackColor = Color.GreenYellow
        tb_radius.Enabled = True
        tb_radius.BackColor = Color.GreenYellow

        b_zend.Enabled = True
        b_annuleren.Enabled = True

        SerialPort1.Write("q")
        rtb_Terminal.Text = rtb_Terminal.Text + "PC: stuur 'd'" + vbCr
    End Sub

    ' Button ronddraaien
    Private Sub b_rondas_Click(sender As Object, e As EventArgs) Handles b_rondas.Click
        Reset_Controls()
        b_rondas.BackColor = Color.GreenYellow
        'Disable_Controls()

        tb_snelheid.Enabled = True
        tb_snelheid.BackColor = Color.GreenYellow
        tb_draaihoek.Enabled = True
        tb_draaihoek.BackColor = Color.GreenYellow

        b_zend.Enabled = True
        b_annuleren.Enabled = True

        rtb_Terminal.Text = rtb_Terminal.Text + "NC" + vbCr
    End Sub

    ' Button stop
    Private Sub b_stop_Click(sender As Object, e As EventArgs) Handles b_stop.Click
        Reset_Controls()
        SerialPort1.Write("a")
        rtb_Terminal.Text = rtb_Terminal.Text + "PC: stuur 'a'" + vbCr
        Reset_Controls()
    End Sub

    ' Button zenden
    Private Sub b_zend_Click(sender As Object, e As EventArgs) Handles b_zend.Click
        If (b_forward.BackColor.Equals(Color.GreenYellow)) Then

        ElseIf (b_left.BackColor.Equals(Color.GreenYellow)) Then

        ElseIf (b_rondas.BackColor.Equals(Color.GreenYellow)) Then

        ElseIf (b_right.BackColor.Equals(Color.GreenYellow)) Then

        ElseIf (b_backward.BackColor.Equals(Color.GreenYellow)) Then

        End If
        rtb_Terminal.Text = rtb_Terminal.Text + "NC" + vbCr
    End Sub

    ' Button annuleren
    Private Sub b_annuleren_Click(sender As Object, e As EventArgs) Handles b_annuleren.Click
        tb_afstand.Text = ""
        tb_afstand.Enabled = False
        tb_snelheid.Text = ""
        tb_snelheid.Enabled = False
        tb_draaihoek.Text = ""
        tb_draaihoek.Enabled = False
        tb_radius.Text = ""
        tb_radius.Enabled = False

        b_zend.Enabled = False
        b_annuleren.Enabled = False

        Enable_Controls()
        Reset_Controls()
    End Sub

    ' Enable alle controle buttons
    Private Sub Enable_Controls()
        b_pingl.Enabled = True
        b_pingm.Enabled = True
        b_pingr.Enabled = True
        b_forward.Enabled = True
        b_stop.Enabled = True
        b_left.Enabled = True
        b_rondas.Enabled = True
        b_right.Enabled = True
        b_backward.Enabled = True
    End Sub

    ' Disable alle controle buttons
    Private Sub Disable_Controls()
        b_pingl.Enabled = False
        b_pingm.Enabled = False
        b_pingr.Enabled = False
        b_forward.Enabled = False
        b_stop.Enabled = False
        b_left.Enabled = False
        b_rondas.Enabled = False
        b_right.Enabled = False
        b_backward.Enabled = False
    End Sub

    ' Resetten van het controlpaneel
    Private Sub Reset_Controls()
        b_pingl.BackColor = Color.LightSteelBlue
        b_pingm.BackColor = Color.LightSteelBlue
        b_pingr.BackColor = Color.LightSteelBlue
        b_forward.BackColor = Color.LightSteelBlue
        b_stop.BackColor = Color.Red
        b_left.BackColor = Color.LightSteelBlue
        b_rondas.BackColor = Color.LightSteelBlue
        b_right.BackColor = Color.LightSteelBlue
        b_backward.BackColor = Color.LightSteelBlue
        tb_afstand.BackColor = Color.White
        tb_snelheid.BackColor = Color.White
        tb_draaihoek.BackColor = Color.White
        tb_radius.BackColor = Color.White
        tb_afstand.ForeColor = Color.DeepSkyBlue
        tb_snelheid.ForeColor = Color.DeepSkyBlue
        tb_draaihoek.ForeColor = Color.DeepSkyBlue
        tb_radius.ForeColor = Color.DeepSkyBlue

        tb_afstand.Enabled = False
        tb_snelheid.Enabled = False
        tb_draaihoek.Enabled = False
        tb_radius.Enabled = False
        tb_afstand.Text = ""
        tb_snelheid.Text = ""
        tb_draaihoek.Text = ""
        tb_radius.Text = ""
    End Sub
End Class
